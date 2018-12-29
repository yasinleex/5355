/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2015. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */

#include "main.h"
/*  Kernel includes. */
#include "FreeRTOS.h"
#include <driver_api.h>
#include <mt_uart.h>
#ifdef CFG_VCORE_DVFS_SUPPORT
#include <dvfs.h>
#endif
#ifdef CFG_LOGGER_SUPPORT
#include <scp_logger.h>
#endif

uint8_t RxByte;         /*Byte de recepcion temporal*/
#ifdef NO_USE_UART
void WriteDebugByte(unsigned int ch)
{
}
#else
void WriteDebugByte(unsigned int ch)
{
    unsigned int LSR;

    //if (DYNAMIC_AP_UART_SWITCH && INFO_SCP_LOG_THRU_AP_UART == 0)
    //    return;

    while (1) {
        LSR = readl(UART_LSR(UART_LOG_PORT));
        if (LSR & UART_LSR_THRE) {
            writel((unsigned int)ch, UART_THR(UART_LOG_PORT));
            break;
        }
    }
}
#endif


#ifdef NO_USE_UART
int ReadDebugByte(void)
{
    return 0;
}
#else
int ReadDebugByte(void)
{
    unsigned int ch;
    unsigned int LSR;

    //if (DYNAMIC_AP_UART_SWITCH && INFO_SCP_LOG_THRU_AP_UART == 0)
    //    return 0;

    LSR = readl(UART_LSR(UART_LOG_PORT));
    if (LSR & UART_LSR_DR) {
        ch = (unsigned int)readl(UART_RBR(UART_LOG_PORT));
    } else {
        ch = DEBUG_SERIAL_READ_NODATA;
    }

    return (int)ch;
}
#endif

/*-----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */
/*-----------------------------------------------------------*/

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE {
    WriteDebugByte(ch);
    return ch;
}

/**
  * @brief  Retargets the C library getc function to the USART.
  * @param  None
  * @retval None
  */
GETCHAR_PROTOTYPE {
    RxByte = ReadDebugByte();
    return RxByte;
}

extern void uart_cust_setting();

#ifdef NO_USE_UART
void uart_init(unsigned int g_uart, unsigned int speed, unsigned int uart_clk_changed)
{

}
#else
void uart_init(unsigned int g_uart, unsigned int speed, unsigned int uart_clk_changed)
{
    unsigned int byte;
    unsigned int highspeed;
    unsigned int quot, divisor, remainder;
    unsigned int uartclk;
    unsigned short data, high_speed_div, sample_count, sample_point;
    unsigned int tmp_div;

    //if (DYNAMIC_AP_UART_SWITCH && INFO_SCP_LOG_THRU_AP_UART == 0)
    //    return;
    //return;

#ifdef USING_APUART_PORT
    /* keep infra online if APUART is select */
    //enable_infra(SCP_A_LOGGER_MEM_ID, NO_WAIT);
#endif
    uart_platform_setting();

    //OUTREG32(CLK_CG_CTRL, INREG(CLK_CG_CTRL) | 0x1F8);
    UART_SET_BITS(UART_FCR(g_uart), UART_FCR_FIFO_INIT); /* clear fifo */
    writel(UART_NONE_PARITY | UART_WLS_8 | UART_1_STOP, UART_LCR(g_uart));
    if (uart_clk_changed != 0)
        uartclk = uart_clk_changed;
    else
        uartclk = UART_SRC_CLK;

    if (speed <= 115200) {
        highspeed = 0;
        quot = 16;
    } else {
        highspeed = 3;
        quot = 1;
    }

    if (highspeed < 3) { /*0~2*/
        /* Set divisor DLL and DLH    */
        divisor   =  uartclk / (quot * speed);
        remainder =  uartclk % (quot * speed);

        if (remainder >= (quot / 2) * speed)
            divisor += 1;

        writel(highspeed, UART_HIGHSPEED(g_uart));
        byte = readl(UART_LCR(g_uart));     /* DLAB start */
        writel((byte | UART_LCR_DLAB), UART_LCR(g_uart));
        writel((divisor & 0x00ff), UART_DLL(g_uart));
        writel(((divisor >> 8) & 0x00ff), UART_DLH(g_uart));
        writel(byte, UART_LCR(g_uart));
    } else {
        data = (unsigned short)(uartclk / speed);
        high_speed_div = (data >> 8) + 1; // divided by 256

        tmp_div = uartclk / (speed * high_speed_div);
        divisor = (unsigned short)tmp_div;

        remainder = (uartclk) % (high_speed_div * speed);
        /*get (sample_count+1)*/
        if (remainder >= ((speed) * (high_speed_div)) >> 1)
            divisor = (unsigned short)(tmp_div + 1);
        else
            divisor = (unsigned short)tmp_div;

        sample_count = divisor - 1;

        /*get the sample point*/
        sample_point = (sample_count - 1) >> 1;

        /*configure register*/
        writel(highspeed, UART_HIGHSPEED(g_uart));
        byte = readl(UART_LCR(g_uart)); /* DLAB start */
        writel((byte | UART_LCR_DLAB), UART_LCR(g_uart));
        writel((high_speed_div & 0x00ff), UART_DLL(g_uart));
        writel(((high_speed_div >> 8) & 0x00ff), UART_DLH(g_uart));
        writel(sample_count, UART_SAMPLE_COUNT(g_uart));
        writel(sample_point, UART_SAMPLE_POINT(g_uart));
        writel(byte, UART_LCR(g_uart));    /* DLAB end */
    }
}
#endif

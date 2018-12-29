
#include "main.h"
#include "FreeRTOS.h"
#include <driver_api.h>
#include <mt_uart.h>



/* Uart Clk Setting */
#define UART0_CK_SEL_MSK    0x3
#define UART0_CK_SEL_SHFT   0
#define UART0_CK_STA_MSK    0xf
#define UART0_CK_STA_SHFT   8
#define UART1_CK_SEL_MSK    0x3
#define UART1_CK_SEL_SHFT   16
#define UART1_CK_STA_MSK    0xf
#define UART1_CK_STA_SHFT   24

enum UART_CTRL_BITS {
    UART_26M = 0,
    UART_32K = 1,
    UART_ULPOSC_DIV12 = 2,
};

void uart_platform_setting(void)
{
#if 0
#ifdef USING_APUART_PORT
    UART_SET_BITS(CLK_AP_CG_CTRL_CLR, CLK_AP_UART1_CLK);
#else

#ifdef CFG_SCP_UART1_SUPPORT
    /* select ulposc_div12 (23.833333M) */
    /* DRV_SetReg32(SCP_UART_CK_SEL, UART_ULPOSC_DIV12 << UART1_CK_SEL_SHFT);
    while((DRV_Reg32(SCP_UART_CK_SEL) & (UART1_CK_STA_MSK << UART1_CK_STA_SHFT)) != (1 << (UART_ULPOSC_DIV12 + UART1_CK_STA_SHFT))); */

    /* scpuart1 backup. GPIO 116/117 (need rework) */
    DRV_WriteReg32(0xA00053E0, (DRV_Reg32(0xA00053E0) & 0xFF00FFFF) | 0x00660000);
    UART_SET_BITS(CLK_CG_CTRL, UART1_CLK | UART1_RST);
#else
    /* select ulposc_div12 (23.833333M) */
    /* DRV_SetReg32(SCP_UART_CK_SEL, UART_ULPOSC_DIV12 << UART0_CK_SEL_SHFT);
    while((DRV_Reg32(SCP_UART_CK_SEL) & (UART0_CK_STA_MSK << UART0_CK_STA_SHFT)) != (1 << (UART_ULPOSC_DIV12 + UART0_CK_STA_SHFT))); */

    /* scpuart0 GPIO 110/112 (reuse apuart1 pin num) */
    DRV_WriteReg32(0xA00053D0, (DRV_Reg32(0xA00053D0) & 0xF0FFFFFF) | 0x03000000);
    DRV_WriteReg32(0xA00053E0, (DRV_Reg32(0xA00053E0) & 0xFFFFFFF0) | 0x00000003);
    UART_SET_BITS(CLK_CG_CTRL, UART0_CLK | UART0_RST); /* enable clock and release reset*/
#endif
#endif
#endif
}

/* Uart Bringup use 26M Clock due to ulposc is not ready during chip bring up.
 * And when ulposc is ready, dvfs.c will call this api to switch uart  to
 * use ulposc clock. 26M clock will disapper when system enter sleep but ulposc
 * will not.
 */
void uart_switch_clk(unsigned int uart_clk_changed)
{
#if 0
#if defined(CFG_UART_SUPPORT)
#ifdef CFG_SCP_UART1_SUPPORT
    /* Set UART_CK_SEL[17:16] = 2'b10: ulposc_div_to_26m for UART1 */
    DRV_ClrReg32(UART_CK_SEL, UART1_CK_SEL_MSK << UART1_CK_SEL_SHFT);
    DRV_SetReg32(UART_CK_SEL, UART_ULPOSC_DIV12 << UART1_CK_SEL_SHFT);

    uart_init(UART_LOG_PORT, UART_LOG_BAUD_RATE, uart_clk_changed * 1000000 / 10);

    /* Check UART_CK_SEL[27:24] = 4'b0100: ulposc_div_to_26m for UART1 */
    while ((DRV_Reg32(UART_CK_SEL) & (UART1_CK_STA_MSK << UART1_CK_STA_SHFT)) !=
            (1 << (UART_ULPOSC_DIV12 + UART1_CK_STA_SHFT)))
        PRINTF_E("uart src status = 0x%x\n", DRV_Reg32(UART_CK_SEL));
#else
    /* Set UART_CK_SEL[1:0] = 2'b10: ulposc_div_to_26m for UART0 */
    DRV_ClrReg32(UART_CK_SEL, UART0_CK_SEL_MSK << UART0_CK_SEL_SHFT);
    DRV_SetReg32(UART_CK_SEL, UART_ULPOSC_DIV12 << UART0_CK_SEL_SHFT);

    uart_init(UART_LOG_PORT, UART_LOG_BAUD_RATE, uart_clk_changed * 1000000 / 10);

    /* Check UART_CK_SEL[11:8] = 4'b0100: ulposc_div_to_26m for UART0 */
    while ((DRV_Reg32(UART_CK_SEL) & (UART0_CK_STA_MSK << UART0_CK_STA_SHFT)) !=
            (1 << (UART_ULPOSC_DIV12 + UART0_CK_STA_SHFT)))
        PRINTF_E("uart src status = 0x%x\n", DRV_Reg32(UART_CK_SEL));
#endif
#endif
#endif
}

/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 *
 * MediaTek Inc. (C) 2018. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */


#include "ovl2_util.h"
#include "wdma2_hw.h"

/* WDMA2 */
#define DISP_REG_WDMA_INTEN                     (0x000UL)
#define DISP_REG_WDMA_INTSTA                    (0x004UL)
#define DISP_REG_WDMA_EN                        (0x008UL)
#define DISP_REG_WDMA_RST                       (0x00CUL)
#define DISP_REG_WDMA_SMI_CON                   (0x010UL)
#define DISP_REG_WDMA_CFG                       (0x014UL)
#define DISP_REG_WDMA_SRC_SIZE                  (0x018UL)
#define DISP_REG_WDMA_CLIP_SIZE                 (0x01CUL)
#define DISP_REG_WDMA_CLIP_COORD                (0x020UL)
#define DISP_REG_WDMA_DST_W_IN_BYTE             (0x028UL)
#define DISP_REG_WDMA_ALPHA                     (0x02CUL)
#define DISP_REG_WDMA_BUF_CON1                  (0x038UL)
#define DISP_REG_WDMA_BUF_CON2                  (0x03CUL)
#define DISP_REG_WDMA_C00                       (0x040UL)
#define DISP_REG_WDMA_C02                       (0x044UL)
#define DISP_REG_WDMA_C10                       (0x048UL)
#define DISP_REG_WDMA_C12                       (0x04CUL)
#define DISP_REG_WDMA_C20                       (0x050UL)
#define DISP_REG_WDMA_C22                       (0x054UL)
#define DISP_REG_WDMA_PRE_ADD0                  (0x058UL)
#define DISP_REG_WDMA_PRE_ADD2                  (0x05CUL)
#define DISP_REG_WDMA_POST_ADD0                 (0x060UL)
#define DISP_REG_WDMA_POST_ADD2                 (0x064UL)
#define DISP_REG_WDMA_DST_UV_PITCH              (0x078UL)
#define DISP_REG_WDMA_DST_ADDR_OFFSET0          (0x080UL)
#define DISP_REG_WDMA_DST_ADDR_OFFSET1          (0x084UL)
#define DISP_REG_WDMA_DST_ADDR_OFFSET2          (0x088UL)
#define DISP_REG_WDMA_FLOW_CTRL_DBG             (0x0A0UL)
#define DISP_REG_WDMA_EXEC_DBG                  (0x0A4UL)
#define DISP_REG_WDMA_CT_DBG                    (0x0A8UL)
#define DISP_REG_WDMA_DEBUG                     (0x0ACUL)
#define DISP_REG_WDMA_DUMMY                     (0x100UL)
#define DISP_REG_WDMA_DITHER_0                  (0xE00UL)
#define DISP_REG_WDMA_DITHER_5                  (0xE14UL)
#define DISP_REG_WDMA_DITHER_6                  (0xE18UL)
#define DISP_REG_WDMA_DITHER_7                  (0xE1CUL)
#define DISP_REG_WDMA_DITHER_8                  (0xE20UL)
#define DISP_REG_WDMA_DITHER_9                  (0xE24UL)
#define DISP_REG_WDMA_DITHER_10                 (0xE28UL)
#define DISP_REG_WDMA_DITHER_11                 (0xE2CUL)
#define DISP_REG_WDMA_DITHER_12                 (0xE30UL)
#define DISP_REG_WDMA_DITHER_13                 (0xE34UL)
#define DISP_REG_WDMA_DITHER_14                 (0xE38UL)
#define DISP_REG_WDMA_DITHER_15                 (0xE3CUL)
#define DISP_REG_WDMA_DITHER_16                 (0xE40UL)
#define DISP_REG_WDMA_DITHER_17                 (0xE44UL)
#define DISP_REG_WDMA_DST_ADDR0                 (0xF00UL)
#define DISP_REG_WDMA_DST_ADDR1                 (0xF04UL)
#define DISP_REG_WDMA_DST_ADDR2                 (0xF08UL)

#define DST_W_IN_BYTE_FLD_DST_W_IN_BYTE         REG_FLD(16, 0)
#define CFG_FLD_OUT_FORMAT                      REG_FLD(4, 4)
#define CFG_FLD_DNSP_SEL                        REG_FLD(1, 15)
#define CFG_FLD_EXT_MTX_EN                      REG_FLD(1, 13)
#define CFG_FLD_CT_EN                           REG_FLD(1, 11)
#define CFG_FLD_INT_MTX_SEL                     REG_FLD(4, 24)
#define CFG_FLD_SWAP                            REG_FLD(1, 16)
#define ALPHA_FLD_A_SEL                         REG_FLD(1, 31)
#define ALPHA_FLD_A_VALUE                       REG_FLD(8, 0)

#define C00_FLD_C01                             REG_FLD(13, 16)
#define C00_FLD_C00                             REG_FLD(13, 0)
#define C02_FLD_C02                             REG_FLD(13, 0)
#define C10_FLD_C11                             REG_FLD(13, 16)
#define C10_FLD_C10                             REG_FLD(13, 0)
#define C12_FLD_C12                             REG_FLD(13, 0)
#define C20_FLD_C21                             REG_FLD(13, 16)
#define C20_FLD_C20                             REG_FLD(13, 0)
#define C22_FLD_C22                             REG_FLD(13, 0)

#define PRE_ADD0_FLD_PRE_ADD_1                  REG_FLD(9, 16)
#define PRE_ADD0_FLD_PRE_ADD_0                  REG_FLD(9, 0)
#define PRE_ADD2_FLD_PRE_ADD_2                  REG_FLD(9, 0)
#define POST_ADD0_FLD_POST_ADD_1                REG_FLD(9, 16)
#define POST_ADD0_FLD_POST_ADD_0                REG_FLD(9, 0)
#define POST_ADD2_FLD_POST_ADD_2                REG_FLD(9, 0)

static const short int coef_rdma_601_r2y[5][3] = {
	{263, 516, 100},
	{-152, -298, 450},
	{450, -377, -73},
	{0, 0, 0},
	{0, 128, 128}
};

static const short int coef_rdma_709_r2y[5][3] = {
	{187, 629, 63},
	{-103, -347, 450},
	{450, -409, -41},
	{0, 0, 0},
	{16, 128, 128}
};

static const short int coef_rdma_601_y2r[5][3] = {
	{1193, 0, 1633},
	{1193, -400, -832},
	{1193, 2065, 0},
	{-16, -128, -128},
	{0, 0, 0}
};

static const short int coef_rdma_709_y2r[5][3] = {
	{1193, 0, 1934},
	{1193, -217, -545},
	{1193, 2163, -1},
	{-16, -128, -128},
	{0, 0, 0}
};

static const uint32_t coef[10][5][3] = {
	/* YUV to RGB SD */
	/* yuv2rgb_601_16_16, y=16~235, uv=16~240, rgb=16~235 */
	{{ 0x0400, 0x0000, 0x057c},  /* 1,  0    ,  1.371    13bit: sign+2.10 */
	{ 0x0400, 0x1ea8, 0x1d35 },  /* 1, -0.336, -0.698    13bit: sign+2.10 */
	{ 0x0400, 0x06ee, 0x0000 },  /* 1,  1.732,  0        13bit: sign+2.10 */
	{      0, 0x180, 0x180  },  /* 0, -128  , -128       9bit: sign+8.0 */
	{      0,      0,      0 } },

	/* yuv2rgb_601_16_0, y=16~235, uv=16~240, rgb=0~255 */
	{{ 0x04a7, 0x0000, 0x0662 },/* 1.164, 0, 1.596 13bit: sign+2.10 */
	{ 0x04a7, 0x1e70, 0x1cc0 }, /* 1.164, -0.391, -0.813 13bit: sign+2.10 */
	{ 0x04a7, 0x0812, 0x0000 }, /* 1.164,  2.018,  0     13bit: sign+2.10 */
	{ 0x1f0, 0x180, 0x180  }, /* -16, -128, -128     9bit: sign+8.0 */
	{      0,      0,      0 } },
	/* yuv2rgb_601_0_0, yuv=0~255, rgb=0~255 */
	{{ 0x0400, 0x0000, 0x059b }, /* 1,  0     ,  1.402   13bit: sign+2.10 */
	{ 0x0400, 0x1ea0, 0x1d25 },  /* 1, -0.3341, -0.7141  13bit: sign+2.10 */
	{ 0x0400, 0x0716, 0x0000 },  /* 1,  1.772 ,  0       13bit: sign+2.10 */
	{      0, 0x180, 0x180  },  /* 0, -128  , -128      9bit: sign+8.0 */
	{      0,      0,      0 } },
	/* YUV to RGB HD */
	/* yuv2rgb_709_16_16, y=16~235, uv=16~240, rgb=16~235 */
	{{ 0x0400, 0x0000, 0x0628 }, /* 1,  0    ,  1.54  13bit: sign+2.10 */
	{ 0x0400, 0x1f45, 0x1e2a },  /* 1, -0.183, -0.459 13bit: sign+2.10 */
	{ 0x0400, 0x0743, 0x0000 },  /* 1,  1.816,  0     13bit: sign+2.10 */
	{      0, 0x180, 0x180  },  /* 0, -128  , -128   9bit: sign+8.0 */
	{      0,      0,      0 } },
	/* yuv2rgb_709_16_0, y=16~235, uv=16~240, rgb=0~255 */
	{{ 0x04a7, 0x0000, 0x072c },/* 1.164,  0    ,  1.793 13bit: sign+2.10 */
	{ 0x04a7, 0x1f26, 0x1dde }, /* 1.164, -0.213, -0.534 13bit: sign+2.10 */
	{ 0x04a7, 0x0875, 0x0000 }, /* 1.164,  2.115,  0     13bit: sign+2.10 */
	{ 0x1f0, 0x180, 0x180  }, /* -16, -128  , -128     9bit: sign+8.0 */
	{      0,      0,      0 } },
	/* yuv2rgb_709_0_0, yuv=0~255, rgb=0~255  */
	{{ 0x0400, 0x0000, 0x064d }, /* 1,  0     ,  1.5748  13bit: sign+2.10 */
	{ 0x0400, 0x1f40, 0x1e21 },  /* 1, -0.1873, -0.4681  13bit: sign+2.10 */
	{ 0x0400, 0x076c, 0x0000 },  /* 1,  1.8556,  0       13bit: sign+2.10 */
	{      0, 0x180, 0x180  },  /* 0, -128   , -128     9bit: sign+8.0 */
	{      0,      0,      0 } },
	/* RGB to YUV SD */
	/* rgb2yuv_601, rgb=0~255, y=16~235, uv=16~240 */
	{{ 0x0107, 0x0204, 0x0064 },/* 0.257,  0.504,  0.098 13bit:sign+2.10 */
	{ 0x1f68, 0x1ed6, 0x01c2 }, /*-0.148, -0.291,  0.439 13bit:sign+2.10 */
	{ 0x01c2, 0x1e87, 0x1fb7 }, /* 0.439, -0.368, -0.071 13bit:sign+2.10 */
	{      0,      0,      0 },
	{ 0x010, 0x080, 0x080  } },/*    16,    128 ,    128 9bit:sign+8.0 */
	/* rgb2yuv_601_xvycc, rgb=0~255, yuv=0~255 */
	{ { 0x0132, 0x0259, 0x0075},/* 0.299 ,  0.587, 0.114 13bit: sign+2.10*/
	{ 0x1f53, 0x1ead, 0x0200 }, /*-0.1687, -0.3313, 0.5   13bit: sign+2.10*/
	{ 0x0200, 0x1e53, 0x1fad }, /* 0.5 , -0.4187, -0.0813 13bit: sign+2.10*/
	{      0,      0,      0 },
	{ 0x010, 0x080, 0x080  } },/* 16 ,    128 ,    128   9bit: sign+8.0*/
	/* RGB to YUV SD */
	/* rgb2yuv_709, rgb=0~255, y=16~235, uv=16~240 */
	{ { 0x00bb, 0x0275, 0x003f},/* 0.183,  0.614,  0.062 13bit: sign+2.10*/
	{ 0x1f98, 0x1ea6, 0x01c2 }, /*-0.101, -0.338,  0.439 13bit: sign+2.10*/
	{ 0x01c2, 0x1e67, 0x1fd7 }, /* 0.439, -0.399, -0.04  13bit: sign+2.10*/
	{      0,      0,      0 },
	{ 0x010, 0x080, 0x080  } },/*    16,    128,  128   9bit: sign+8.0*/
	/* rgb2yuv_709_xvycc, rgb=0~255, yuv=0~255 */
	{{ 0x00da, 0x02dc, 0x004a },/* 0.2126,  0.7152, 0.0722 13bit:sign+2.10*/
	{ 0x1f8b, 0x1e75, 0x0200 }, /*-0.1146, -0.3854, 0.5    13bit:sign+2.10*/
	{ 0x0200, 0x1e2f, 0x1fd1 }, /* 0.5, -0.4542, -0.0458 13bit:sign+2.10*/
	{      0,      0,      0 },
	{ 0x010, 0x080, 0x080  } } /* 16,    128 ,    128  9bit:sign+8.0*/
};

uint32_t mtk_wdma2_hw_output_format_byte_swap(
	enum MTK_WDMA_HW_FORMAT outputFormat)
{
	uint32_t output_swap = 0;

	OVL2_LOG_FUNC_START;

	switch (outputFormat) {
	case MTK_WDMA_HW_FORMAT_BGR565:
	case MTK_WDMA_HW_FORMAT_RGB888:
	case MTK_WDMA_HW_FORMAT_RGBA8888:
	case MTK_WDMA_HW_FORMAT_ARGB8888:
	case MTK_WDMA_HW_FORMAT_VYUY:
	case MTK_WDMA_HW_FORMAT_YVYU:
	case MTK_WDMA_HW_FORMAT_NV21:
	case MTK_WDMA_HW_FORMAT_YV12:
		output_swap = 1;
		break;
	case MTK_WDMA_HW_FORMAT_RGB565:
	case MTK_WDMA_HW_FORMAT_BGR888:
	case MTK_WDMA_HW_FORMAT_BGRA8888:
	case MTK_WDMA_HW_FORMAT_ABGR8888:
	case MTK_WDMA_HW_FORMAT_UYVY:
	case MTK_WDMA_HW_FORMAT_YUYV:
	case MTK_WDMA_HW_FORMAT_NV12:
	case MTK_WDMA_HW_FORMAT_IYUV:
	/*case MTK_WDMA_HW_FORMAT_YONLY:*/
		output_swap = 0;
		break;
	default:
		OVL2_LOG_E("%s[%d] unsupport wdma output fmt=0x%x",
			__func__, __LINE__, outputFormat);
		break;
	}

	return output_swap;
}

static uint32_t mtk_wdma2_hw_output_format_bpp(
	enum MTK_WDMA_HW_FORMAT outputFormat)
{
	uint32_t bpp = 0;

	OVL2_LOG_FUNC_START;

	switch (outputFormat) {
	case MTK_WDMA_HW_FORMAT_IYUV:
	case MTK_WDMA_HW_FORMAT_NV12:
	case MTK_WDMA_HW_FORMAT_NV21:
	case MTK_WDMA_HW_FORMAT_YV12:
	case MTK_WDMA_HW_FORMAT_YONLY:
		bpp = 1;
		break;
	case MTK_WDMA_HW_FORMAT_BGR565:
	case MTK_WDMA_HW_FORMAT_RGB565:
	case MTK_WDMA_HW_FORMAT_VYUY:
	case MTK_WDMA_HW_FORMAT_UYVY:
	case MTK_WDMA_HW_FORMAT_YVYU:
	case MTK_WDMA_HW_FORMAT_YUYV:
		bpp = 2;
		break;
	case MTK_WDMA_HW_FORMAT_RGB888:
	case MTK_WDMA_HW_FORMAT_BGR888:
		bpp = 3;
		break;
	case MTK_WDMA_HW_FORMAT_ARGB8888:
	case MTK_WDMA_HW_FORMAT_ABGR8888:
	case MTK_WDMA_HW_FORMAT_RGBA8888:
	case MTK_WDMA_HW_FORMAT_BGRA8888:
		bpp = 4;
		break;
	default:
		OVL2_LOG_E("%s[%d] unsupport wdma output fmt=0x%x",
			__func__, __LINE__, outputFormat);
		break;
	}

	return bpp;
}

static enum WDMA_COLOR_SPACE mtk_wdma2_hw_output_format_color_space(
	enum MTK_WDMA_HW_FORMAT outputFormat)
{
	enum WDMA_COLOR_SPACE space = WDMA_COLOR_SPACE_RGB;

	OVL2_LOG_FUNC_START;

	switch (outputFormat) {
	case MTK_WDMA_HW_FORMAT_BGR565:
	case MTK_WDMA_HW_FORMAT_RGB565:
	case MTK_WDMA_HW_FORMAT_RGB888:
	case MTK_WDMA_HW_FORMAT_BGR888:
	case MTK_WDMA_HW_FORMAT_RGBA8888:
	case MTK_WDMA_HW_FORMAT_BGRA8888:
	case MTK_WDMA_HW_FORMAT_ARGB8888:
	case MTK_WDMA_HW_FORMAT_ABGR8888:
		space = WDMA_COLOR_SPACE_RGB;
		break;
	case MTK_WDMA_HW_FORMAT_VYUY:
	case MTK_WDMA_HW_FORMAT_UYVY:
	case MTK_WDMA_HW_FORMAT_YVYU:
	case MTK_WDMA_HW_FORMAT_YUYV:
	case MTK_WDMA_HW_FORMAT_IYUV:
	case MTK_WDMA_HW_FORMAT_NV12:
	case MTK_WDMA_HW_FORMAT_NV21:
	case MTK_WDMA_HW_FORMAT_YONLY:
	case MTK_WDMA_HW_FORMAT_YV12:
		space = WDMA_COLOR_SPACE_YUV;
		break;
	default:
		OVL2_LOG_E("%s[%d] unsupport wdma output fmt=0x%x",
			__func__, __LINE__, outputFormat);
		break;
	}

	return space;
}

static uint32_t mtk_wdma2_hw_output_fmt_reg_value(
	enum MTK_WDMA_HW_FORMAT outputFormat)
{
	uint32_t reg_value = 0x1;

	OVL2_LOG_FUNC_START;

	switch (outputFormat) {
	case MTK_WDMA_HW_FORMAT_BGR565:
	case MTK_WDMA_HW_FORMAT_RGB565:
		reg_value = 0x0;
		break;
	case MTK_WDMA_HW_FORMAT_RGB888:
	case MTK_WDMA_HW_FORMAT_BGR888:
		reg_value = 0x1;
		break;
	case MTK_WDMA_HW_FORMAT_RGBA8888:
	case MTK_WDMA_HW_FORMAT_BGRA8888:
		reg_value = 0x2;
		break;
	case MTK_WDMA_HW_FORMAT_ARGB8888:
	case MTK_WDMA_HW_FORMAT_ABGR8888:
		reg_value = 0x3;
		break;
	case MTK_WDMA_HW_FORMAT_VYUY:
	case MTK_WDMA_HW_FORMAT_UYVY:
		reg_value = 0x4;
		break;
	case MTK_WDMA_HW_FORMAT_YVYU:
	case MTK_WDMA_HW_FORMAT_YUYV:
		reg_value = 0x5;
		break;
	case MTK_WDMA_HW_FORMAT_YONLY:
		reg_value = 0x7;
		break;
	case MTK_WDMA_HW_FORMAT_IYUV:
	case MTK_WDMA_HW_FORMAT_YV12:
		reg_value = 0x8;
		break;
	case MTK_WDMA_HW_FORMAT_NV12:
	case MTK_WDMA_HW_FORMAT_NV21:
		reg_value = 0xc;
		break;
	default:
		OVL2_LOG_E("%s[%d] unsupport wdma output fmt=0x%x",
			__func__, __LINE__, outputFormat);
		break;
	}

	return reg_value;
}

void mtk_wdma2_hw_irq_clear(unsigned long reg_base)
{
	unsigned int val = 0;
	unsigned long addr = (unsigned long)reg_base + DISP_REG_WDMA_INTSTA;

	OVL2_LOG_FUNC_START;

	val = DISP_REG_GET(addr);

	if ((val & 0x1u) == 0x1u) {
		OVL2_LOG_D("ok to confirm wdma irq 0x%lx = 0x%x",
			addr, val);
		DISP_REG_SET(addr, 0x0);
		OVL2_LOG_D("clear wdma irq 0x%lx = 0x%x",
			addr, DISP_REG_GET(addr));
	} else {
		OVL2_LOG_E("fail to confirm wdma irq 0x%lx = 0x%x",
			addr, val);
	}
}

static int32_t mtk_wdma2_hw_enable(unsigned long reg_base)
{
	OVL2_LOG_FUNC_START;

	DISP_REG_SET(reg_base + DISP_REG_WDMA_INTEN, 0x03);
	DISP_REG_SET(reg_base + DISP_REG_WDMA_EN, 0x01);

	return 0;
}

static int32_t mtk_wdma2_hw_disable(unsigned long reg_base)
{
	OVL2_LOG_FUNC_START;

	DISP_REG_SET(reg_base + DISP_REG_WDMA_INTEN, 0x00);
	DISP_REG_SET(reg_base + DISP_REG_WDMA_EN, 0x00);
	DISP_REG_SET(reg_base + DISP_REG_WDMA_INTSTA, 0x00);

	return 0;
}

static int32_t mtk_wdma2_hw_reset(unsigned long reg_base)
{
	uint32_t delay_cnt = 0;

	OVL2_LOG_FUNC_START;

	DISP_REG_SET(reg_base + DISP_REG_WDMA_RST, 0x1);
	while ((DISP_REG_GET(reg_base + DISP_REG_WDMA_FLOW_CTRL_DBG) & 0x1u)
			== 0U) {
		delay_cnt++;
		if (delay_cnt > 10000u) {
			OVL2_LOG_E("fail to do wdma hw reset\n");
			break;
		}
	}
	DISP_REG_SET(reg_base + DISP_REG_WDMA_RST, 0x0);

	return 0;
}

static int32_t mtk_wdma2_hw_config(unsigned long reg_base,
	struct MTK_WDMA2_HW_PARAM *pParam)
{
	uint32_t output_swap = 0;
	enum WDMA_COLOR_SPACE input_color_space = WDMA_COLOR_SPACE_RGB;
	enum WDMA_COLOR_SPACE output_color_space = WDMA_COLOR_SPACE_RGB;
	uint32_t mode = 0xdeaddeadU;
	uint32_t bpp = 0;
	uint32_t out_fmat = 0;

	OVL2_LOG_FUNC_START;

	out_fmat = mtk_wdma2_hw_output_fmt_reg_value(pParam->out_format);

	DISP_REG_SET(
		reg_base + DISP_REG_WDMA_SRC_SIZE,
		pParam->src_height << 16 | pParam->src_width);
	DISP_REG_SET(
		reg_base + DISP_REG_WDMA_CLIP_COORD,
		pParam->clip_y << 16 | pParam->clip_x);
	DISP_REG_SET(
		reg_base + DISP_REG_WDMA_CLIP_SIZE,
		pParam->clip_height << 16 | pParam->clip_width);
	DISP_REG_SET_FIELD(
		CFG_FLD_OUT_FORMAT,
		reg_base + DISP_REG_WDMA_CFG,
		out_fmat & 0xfu);
	DISP_REG_SET_FIELD(
		CFG_FLD_DNSP_SEL,
		reg_base + DISP_REG_WDMA_CFG,
		((
			(pParam->out_format == MTK_WDMA_HW_FORMAT_UYVY) ||
			(pParam->out_format == MTK_WDMA_HW_FORMAT_VYUY) ||
			(pParam->out_format == MTK_WDMA_HW_FORMAT_YUYV) ||
			(pParam->out_format == MTK_WDMA_HW_FORMAT_YVYU) ||
			(pParam->out_format == MTK_WDMA_HW_FORMAT_YV12)
		) ? 1 : 0));

	switch (pParam->in_format) {
	case MTK_WDMA_HW_FORMAT_RGB565:
	case MTK_WDMA_HW_FORMAT_RGB888:
	case MTK_WDMA_HW_FORMAT_RGBA8888:
	case MTK_WDMA_HW_FORMAT_ARGB8888:
	case MTK_WDMA_HW_FORMAT_BGR565:
	case MTK_WDMA_HW_FORMAT_BGR888:
	case MTK_WDMA_HW_FORMAT_BGRA8888:
	case MTK_WDMA_HW_FORMAT_ABGR8888:
		input_color_space = WDMA_COLOR_SPACE_RGB;
		break;
	case MTK_WDMA_HW_FORMAT_UYVY:
	case MTK_WDMA_HW_FORMAT_YUYV:
	case MTK_WDMA_HW_FORMAT_NV21:
	case MTK_WDMA_HW_FORMAT_YV12:
	case MTK_WDMA_HW_FORMAT_VYUY:
	case MTK_WDMA_HW_FORMAT_YVYU:
	case MTK_WDMA_HW_FORMAT_YONLY:
	case MTK_WDMA_HW_FORMAT_NV12:
	case MTK_WDMA_HW_FORMAT_IYUV:
		input_color_space = WDMA_COLOR_SPACE_YUV;
		break;
	default:
		OVL2_LOG_E("%s[%d] unsupport input fmt = %d",
			__func__, __LINE__, pParam->in_format);
		break;
	}

	output_color_space =
		mtk_wdma2_hw_output_format_color_space(pParam->out_format);

	if (input_color_space == WDMA_COLOR_SPACE_RGB &&
		output_color_space == WDMA_COLOR_SPACE_YUV) {
		/* RGB to YUV required */
		mode = RGB2YUV_601;
		OVL2_LOG_D("[wdma] hw mode = %u, color_space[%d, %d]",
			mode, input_color_space, output_color_space);
	} else if (input_color_space == WDMA_COLOR_SPACE_YUV &&
		output_color_space == WDMA_COLOR_SPACE_RGB) {
		/* YUV to RGB required */
		mode = YUV2RGB_601_16_16;
		OVL2_LOG_D("[wdma] hw mode = %u, color_space[%d, %d]",
			mode, input_color_space, output_color_space);
	} else {
		OVL2_LOG_D("[wdma] hw mode = %u, color_space[%d, %d]",
			mode, input_color_space, output_color_space);
	}

	if (mode < TABLE_NO) { /* set matrix as mode */
		OVL2_LOG_D("[wdma] will do hw color transform");

		DISP_REG_SET_FIELD(
			C00_FLD_C00,
			reg_base + DISP_REG_WDMA_C00,
			coef[mode][0][0]);
		DISP_REG_SET_FIELD(
			C00_FLD_C01,
			reg_base + DISP_REG_WDMA_C00,
			coef[mode][0][1]);
		DISP_REG_SET(
			reg_base + DISP_REG_WDMA_C02,
			coef[mode][0][2]);

		DISP_REG_SET_FIELD(
			C10_FLD_C10,
			reg_base + DISP_REG_WDMA_C10,
			coef[mode][1][0]);
		DISP_REG_SET_FIELD(
			C10_FLD_C11,
			reg_base + DISP_REG_WDMA_C10,
			coef[mode][1][1]);
		DISP_REG_SET(
			reg_base + DISP_REG_WDMA_C12,
			coef[mode][1][2]);

		DISP_REG_SET_FIELD(
			C20_FLD_C20,
			reg_base + DISP_REG_WDMA_C20,
			coef[mode][2][0]);
		DISP_REG_SET_FIELD(
			C20_FLD_C21,
			reg_base + DISP_REG_WDMA_C20,
			coef[mode][2][1]);
		DISP_REG_SET(
			reg_base + DISP_REG_WDMA_C22,
			coef[mode][2][2]);

		DISP_REG_SET_FIELD(
			PRE_ADD0_FLD_PRE_ADD_0,
			reg_base + DISP_REG_WDMA_PRE_ADD0,
			coef[mode][3][0]);
		DISP_REG_SET_FIELD(
			PRE_ADD0_FLD_PRE_ADD_1,
			reg_base + DISP_REG_WDMA_PRE_ADD0,
			coef[mode][3][1]);
		DISP_REG_SET_FIELD(
			PRE_ADD2_FLD_PRE_ADD_2,
			reg_base + DISP_REG_WDMA_PRE_ADD2,
			coef[mode][3][2]);

		DISP_REG_SET_FIELD(
			POST_ADD0_FLD_POST_ADD_0,
			reg_base + DISP_REG_WDMA_POST_ADD0,
			coef[mode][4][0]);
		DISP_REG_SET_FIELD(
			POST_ADD0_FLD_POST_ADD_1,
			reg_base + DISP_REG_WDMA_POST_ADD0,
			coef[mode][4][1]);
		DISP_REG_SET(
			reg_base + DISP_REG_WDMA_POST_ADD2,
			coef[mode][4][2]);

		DISP_REG_SET_FIELD(
			CFG_FLD_EXT_MTX_EN,
			reg_base + DISP_REG_WDMA_CFG,
			1);
		DISP_REG_SET_FIELD(
			CFG_FLD_CT_EN,
			reg_base + DISP_REG_WDMA_CFG,
			1);
	} else {
		OVL2_LOG_D("undo hw color transform");
		DISP_REG_SET_FIELD(
			CFG_FLD_EXT_MTX_EN, reg_base + DISP_REG_WDMA_CFG, 0);
		DISP_REG_SET_FIELD(
			CFG_FLD_CT_EN, reg_base + DISP_REG_WDMA_CFG, 0);
	}

	bpp = mtk_wdma2_hw_output_format_bpp(pParam->out_format);
	output_swap = mtk_wdma2_hw_output_format_byte_swap(pParam->out_format);

	DISP_REG_SET_FIELD(
		CFG_FLD_SWAP,
		reg_base + DISP_REG_WDMA_CFG,
		output_swap);
	DISP_REG_SET(
		reg_base + DISP_REG_WDMA_DST_ADDR0,
		(unsigned int)(pParam->addr_plane));
	DISP_REG_SET(
		reg_base + DISP_REG_WDMA_DST_W_IN_BYTE,
		pParam->src_width * bpp);
	DISP_REG_SET_FIELD(
		ALPHA_FLD_A_SEL,
		reg_base + DISP_REG_WDMA_ALPHA,
		pParam->use_specified_alpha);
	DISP_REG_SET_FIELD(
		ALPHA_FLD_A_VALUE,
		reg_base + DISP_REG_WDMA_ALPHA,
		pParam->alpha);

	return 0;
}

int32_t mtk_wdma2_hw_set(
		unsigned long reg_base, struct MTK_WDMA2_HW_PARAM *pParam)
{
	int32_t ret = 0;

	OVL2_LOG_FUNC_START;

	if (pParam == NULL) {
		OVL2_LOG_E("invalid param[0x%p] in %s",
			pParam, __func__);
		return -1;
	}

	ret = mtk_wdma2_hw_reset(reg_base);
	ret = mtk_wdma2_hw_config(reg_base, pParam);
	ret = mtk_wdma2_hw_enable(reg_base);

	return ret;
}

int32_t mtk_wdma2_hw_unset(unsigned long reg_base)
{
	int32_t ret = 0;

	OVL2_LOG_FUNC_START;

	ret = mtk_wdma2_hw_disable(reg_base);

	return ret;
}


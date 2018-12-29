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

/*
* Author: Huangfei Xiao <huangfei.xiao@mediatek.com>
*/

#ifndef FASTRVC_SETTING_H
#define FASTRVC_SETTING_H

#include <tinysys_config.h>
#include "mt_reg_base.h"
#include "video_core.h"
#include "gpio.h"

#define ALIGN(x, a)			((x + a - 1) & (~(a - 1)))
#define ARGB_IMAGE_SIZE(w, h)		((w) * (h) * 4)
#define YUYV_IMAGE_SIZE(w, h)		((w) * (h) * 2)
#define MT21_IMAGE_SIZE(w, h)		( ALIGN(w, 16) * (ALIGN(h, 32) + ALIGN(ALIGN(h, 32) / 2, 32)) )

#define CAMERA_PIX_FMT			PIX_FMT_MT21
#define CAMERA_RESOLUTION_WIDTH		720
#define CAMERA_RESOLUTION_HEIGHT	480
#define CAMERA_IMAGE_SIZE		MT21_IMAGE_SIZE(CAMERA_RESOLUTION_WIDTH, CAMERA_RESOLUTION_HEIGHT)

/*
* display overlay has private fourcc value
* but must be sure the color format are same
*/
#define DISPLAY_PIX_FMT			PIX_FMT_YUYV
#define DISPLAY_OVL_FMT			PIX_DISP_YUYV
#define DISPLAY_RESOLUTION_WIDTH	1920
#define DISPLAY_RESOLUTION_HEIGHT	1080
#define DISPLAY_IMAGE_SIZE		YUYV_IMAGE_SIZE(DISPLAY_RESOLUTION_WIDTH, DISPLAY_RESOLUTION_HEIGHT)

#ifdef CFG_FASTLOGO_SUPPORT
#define FASTLOGO_ADDRESS		SCP_LOGO_IMG_BASE
#define FASTLOGO_PIX_FMT		PIX_DISP_BGR24
#endif

#ifdef CFG_FASTRVC_GUIDELINE_SUPPORT
#define GUIDELINE_ADDRESS		SCP_GUIDELINE_IMG_BASE
#define GUIDELINE_PIX_FMT		PIX_FMT_ARGB32
#endif

#define REVERSE_GEAR_GPIO		GPIO135

#endif //FASTRVC_SETTING_H
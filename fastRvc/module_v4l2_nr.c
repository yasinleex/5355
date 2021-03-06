/*
* Copyright Statement:
*
* This software/firmware and related documentation ("MediaTek Software") are
* protected under relevant copyright laws. The information contained herein is
* confidential and proprietary to MediaTek Inc. and/or its licensors. Without
* the prior written permission of MediaTek inc. and/or its licensors, any
* reproduction, modification, use or disclosure of MediaTek Software, and
* information contained herein, in whole or in part, shall be strictly
* prohibited.
*
* MediaTek Inc. (C) 2015. All rights reserved.
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
*/
#include "module_v4l2.h"

typedef struct v4l2_nr_device {
	// common
	v4l2_device v4l2_base;
	// private
	unsigned int bnr_level; //
	unsigned int mnr_level; // 
	unsigned int fnr_level; // 
} v4l2_nr_device;

static void v4l2_nr_driver_config(struct module *mod, char *name, unsigned long value)
{
	struct v4l2_nr_device *dev;
	dev = (v4l2_nr_device*)module_get_driver_data(mod);

	if (strcmp(name, "bnr_level") == 0) {
		dev->bnr_level = value;;
	} else if (strcmp(name, "mnr_level") == 0) {
		dev->mnr_level = value;;
	} else if (strcmp(name, "fnr_level") == 0) {
		dev->fnr_level = value;;
	} else {
		v4l2_driver_config(mod, name, value);
	}
}

static int v4l2_nr_driver_init(struct module *mod)
{
	struct v4l2_device *dev;
	struct v4l2_nr_device *nr_dev;
	nr_dev = (v4l2_nr_device*)module_get_driver_data(mod);
	dev = (v4l2_device*)nr_dev;

	// do base init
	if (v4l2_driver_init(mod) != 0)
		return -1;

	//v4l2_s_control(dev->fd, CID_XXX, nr_dev->bnr_level);
	//v4l2_s_control(dev->fd, CID_XXX, nr_dev->mnr_level);
	//v4l2_s_control(dev->fd, CID_XXX, nr_dev->fnr_level);

	unsigned int level;
	level = (nr_dev->bnr_level << 16) | (nr_dev->mnr_level << 8) | nr_dev->fnr_level;
	v4l2_ioctl(dev->fd, VIDIOC_S_INPUT, &level);

	return 0;
}

static module_driver v4l2_nr_driver = {
	.config = v4l2_nr_driver_config,
	.init = v4l2_nr_driver_init,
	.deinit = v4l2_driver_deinit,
	.handle_frame = v4l2_driver_handle_frame,
};

int v4l2_nr_module_init(module *mod)
{
	struct v4l2_nr_device *dev;
	dev = (v4l2_nr_device*)malloc(sizeof(v4l2_nr_device));
	memset(dev, 0, sizeof(*dev));

	module_set_name(mod, "v4l2_nr");
	module_register_driver(mod, &v4l2_nr_driver, dev);
	module_register_allocator(mod, &v4l2_mem_ops, dev);
	return 0;
}

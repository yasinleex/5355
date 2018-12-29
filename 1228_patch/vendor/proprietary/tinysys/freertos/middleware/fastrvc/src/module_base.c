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

#include <stdlib.h>
#include <string.h>
#include "fastrvc/module.h"

typedef struct base_device {
	char		*name;
	void 		*handle;
	base_config 	config;
	video_buffer 	*buffer;
} base_device;

void base_buffer_done(void *usr_data, video_buffer_type type, video_buffer *buffer)
{
	base_device *dev;
	module *mod = (module*)usr_data;

	if (!usr_data || !buffer)
		return;

	dev = (base_device*)module_driver_data(mod);

	if (type == VIDEO_BUFFER_INPUT)
		module_prev_push_buffer(mod, VIDEO_BUFFER_OUTPUT, buffer);
	else if (type == VIDEO_BUFFER_OUTPUT)
		module_next_push_buffer(mod, VIDEO_BUFFER_INPUT, buffer);
	else
		LOGE("%s: unknown buffer type %d\n", dev->name, type);
}

int32_t module_base_config(module *mod, uint32_t type, void *config)
{
	(void)type;

	base_device *dev = (base_device*)module_driver_data(mod);
	memcpy(&(dev->config), config, sizeof(dev->config));

	if (!dev->config.dev_name) {
		LOGE("dev_name can't be null\n");
		return -1;
	}

	dev->name = dev->config.dev_name;
	module_set_name(mod, dev->name);
	return 0;
}

int32_t module_base_init(module *mod)
{
	int i;
	base_device *dev = (base_device*)module_driver_data(mod);

	dev->buffer = (video_buffer*)malloc(sizeof(*(dev->buffer)) * dev->config.buffer_count);
	for (i = 0; i < dev->config.buffer_count; i++) {
		dev->buffer[i].image = noncached_mem_alloc(dev->config.buffer_size);
		//dev->buffer[i].image = malloc(dev->config.buffer_size);
		if (!dev->buffer[i].image) {
			LOGE("%s: alloc memory fail\n", dev->name);
			return -1;
		}

		LOGD("%s: noncached_mem_alloc %p size %ld\n", dev->name, dev->buffer[i].image, dev->config.buffer_size);
		dev->buffer[i].image = VA_TO_IOVA(dev->buffer[i].image);
	}
	return 0;
}

void module_base_deinit(module *mod)
{
	int i;
	base_device *dev = (base_device*)module_driver_data(mod);

	if (dev->buffer == NULL)
		return;

	for (i = 0; i < dev->config.buffer_count; i++) {
		 //noncached_mem_free(IOVA_TO_VA(dev->buffer[i].image));
		 //free(dev->buffer[i].image);
		 dev->buffer[i].image = NULL;
	}
	free(dev->buffer);
	dev->buffer = NULL;
}

int32_t module_base_start(module *mod)
{
	int i;
	base_device *dev = (base_device*)module_driver_data(mod);

	dev->handle = video_core_open(dev->name);
	if (!dev->handle) {
		LOGE("%s: device open fail\n", dev->name ? dev->name : "null");
		return -1;
	}

	if (dev->config.input_format.width) {
		if (0 != video_core_config(dev->handle, VIDEO_CONFIG_FORMAT, &(dev->config.input_format))) {
			LOGE("%s: config input_format error\n", dev->name);
			goto err;
		}
	}
	if (dev->config.input_rect.width) {
		if (0 != video_core_config(dev->handle, VIDEO_CONFIG_CROP, &(dev->config.input_rect))) {
			LOGE("%s: config input_rect error\n", dev->name);
			goto err;
		}
	}
	if (dev->config.output_format.width) {
		if (0 != video_core_config(dev->handle, VIDEO_CONFIG_FORMAT, &(dev->config.output_format))) {
			LOGE("%s: config output_format error\n", dev->name);
			goto err;
		}
	}
	if (dev->config.output_rect.width) {
		if (0 != video_core_config(dev->handle, VIDEO_CONFIG_CROP, &(dev->config.output_rect))) {
			LOGE("%s: config output_rect error\n", dev->name);
			goto err;
		}
	}

	video_core_register_handler(dev->handle, base_buffer_done, mod);

	for (i = 0; i < dev->config.buffer_count; i++) {
		if (0 != video_core_commit(dev->handle, VIDEO_BUFFER_OUTPUT, &dev->buffer[i])) {
			LOGE("%s: commit buffer error\n", dev->name);
			goto err;
		}
	}

	return 0;
err:
	video_core_close(dev->handle);
	return -1;
}

int32_t module_base_stop(module *mod)
{
	base_device *dev = (base_device*)module_driver_data(mod);
	return video_core_close(dev->handle);
}

int32_t module_base_commit(module *mod, video_buffer_type type, video_buffer *buffer)
{
	base_device *dev = (base_device*)module_driver_data(mod);
	if (!buffer)
		return -1;

	if (type != VIDEO_BUFFER_INPUT && type != VIDEO_BUFFER_OUTPUT) {
		LOGE("%s: error buffer type %d\n", dev->name, type);
		return -1;
	}

	return video_core_commit(dev->handle, type, buffer);
}


static module_driver module_base = {
	.config = module_base_config,
	.init = module_base_init,
	.deinit = module_base_deinit,
	.start = module_base_start,
	.stop = module_base_stop,
	.commit = module_base_commit,
};

int32_t base_module_create(module *mod)
{
	base_device *dev = (base_device*)malloc(sizeof(base_device));
	if (!dev) {
		LOGE("malloc fail\n");
		return -1;
	}

	memset(dev, sizeof(*dev), 0);
	/*
	* drvier_data free by module_destroy
	*/
	module_register_driver(mod, &module_base, dev);
	return 0;
}
###############################################################
LOCAL_PATH := $(call my-dir)


###############################################################
# build allocate test's executable
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	drm_display.c \
	gpu_render.cpp \
	main.c 

LOCAL_C_INCLUDES += \
	external/libpng \
	external/libdrm \
	external/libdrm/include/drm \
	external/libxml2/include \
	system/core/base/include \
	vendor/mediatek/mt2712/mtkgpudisp

LOCAL_SHARED_LIBRARIES := \
	libbase \
	libutils \
	libdrm \
	libhardware


LOCAL_MODULE := mtkgpudisp
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS += -Wno-pointer-bool-conversion -Wno-tautological-pointer-compare
LOCAL_LDLIBS += -lm -llog -lGLESv2 -lEGL

include $(BUILD_EXECUTABLE)

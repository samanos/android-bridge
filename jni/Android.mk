# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

VENDOR_PROTOCOL := vendor/protocol
VENDOR_USB_INTERFACE := vendor/usb-interface

include $(CLEAR_VARS)

LOCAL_MODULE    := android_bridge
LOCAL_SRC_FILES := android_bridge.c

LOCAL_C_INCLUDES += \
	$(VENDOR_PROTOCOL)/src \
	$(VENDOR_USB_INTERFACE)/src

LOCAL_SHARED_LIBRARIES += usb_interface

include $(BUILD_SHARED_LIBRARY)

include $(VENDOR_USB_INTERFACE)/android/jni/usb_interface.mk

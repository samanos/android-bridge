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
LIBUSB_SRC := /home/martynas/projects/libusb

include $(CLEAR_VARS)

LOCAL_MODULE    := udal
LOCAL_SRC_FILES := udal.c

LOCAL_C_INCLUDES += $(LIBUSB_SRC)/libusb
LOCAL_SHARED_LIBRARIES += libusb1.0

include $(BUILD_SHARED_LIBRARY)

include $(LIBUSB_SRC)/android/jni/libusb.mk

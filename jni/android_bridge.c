#include <stdio.h>
#include <string.h>
#include <jni.h>

#include "usb_interface.h"
#include "protocol.h"

jstring Java_io_github_samanos_AndroidBridge_queryForData(JNIEnv* env, jobject thiz)
{
  usb_device_id device_id = {
    .vendor_id = VENDOR_ID,
    .vendor_name = VENDOR_NAME,
    .product_id = PRODUCT_ID,
    .product_name = PRODUCT_NAME
  };

  uint8_t reply[32];
  int8_t length = transfer_data2(&device_id, REQUEST_BRIDGE_STATUS, 0x00, reply, sizeof(reply));

  char buffer[256];
  if (length >= 0) {
    sprintf(buffer, "First reply bytes: %02X %02X %02X %02X\n", reply[0], reply[1], reply[2], reply[3]);
    return (*env)->NewStringUTF(env, buffer);
  }
  else {
    sprintf(buffer, "No reply. Length %d\n", length);
    return (*env)->NewStringUTF(env, buffer);
  }
}

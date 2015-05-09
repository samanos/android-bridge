#include <stdio.h>
#include <string.h>
#include <jni.h>

#include "libusb.h"

#include "udal.h"

#define CTRL_IN	(LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE | LIBUSB_ENDPOINT_IN)

jstring Java_lt_dualem_Udal_queryForData(JNIEnv* env, jobject thiz)
{
  libusb_device_handle *handle = NULL;
  char buffer[256];

  int r = libusb_init(NULL);
	if (r < 0)
		return (*env)->NewStringUTF(env, "Error while initializing libUSB.");

  handle = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
  if (!handle)
    return (*env)->NewStringUTF(env, "Unable to find UDAL USB device.");

  r = libusb_control_transfer(handle, CTRL_IN, UDAL_MSG_QUERY_SENSOR, 0, 0, buffer, sizeof(buffer), 0);
  if (r < 0) // error
		return (*env)->NewStringUTF(env, "Error while sending message to a USB device.");

  return (*env)->NewStringUTF(env, buffer);
}

static jstring get_devs(JNIEnv* env, libusb_device **devs)
{
  libusb_device *dev;
  int i = 0, j = 0;
  uint8_t path[8];
  char* buffer;
  int buffer_len = 0;
  jstring devices;

  buffer = malloc(1024);
  strcpy(buffer, "");

  while ((dev = devs[i++]) != NULL) {
    struct libusb_device_descriptor desc;
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) {
      return (*env)->NewStringUTF(env, "failed to get device descriptor");
    }

    buffer_len += sprintf(buffer + buffer_len, "%04x:%04x (bus %d, device %d)",
      desc.idVendor, desc.idProduct,
      libusb_get_bus_number(dev), libusb_get_device_address(dev));

    r = libusb_get_port_numbers(dev, path, sizeof(path));
    if (r > 0) {
      buffer_len += sprintf(buffer + buffer_len, " path: %d", path[0]);
      for (j = 1; j < r; j++)
        buffer_len += sprintf(buffer + buffer_len, ".%d", path[j]);
    }
    buffer_len += sprintf(buffer + buffer_len, "\n");
  }

  devices = (*env)->NewStringUTF(env, buffer);

  free(buffer);

  return devices;
}

jstring Java_lt_dualem_Udal_listDevs(JNIEnv* env, jobject thiz)
{
  libusb_device **devs;
  int r;
  ssize_t cnt;
  jstring device_list;

  r = libusb_init(NULL);
  if (r < 0)
    return (*env)->NewStringUTF(env, "Failed to initialize libusb.");

  cnt = libusb_get_device_list(NULL, &devs);
  if (cnt < 0)
    return (*env)->NewStringUTF(env, "Negative device count.");

  device_list = get_devs(env, devs);
  libusb_free_device_list(devs, 1);

  libusb_exit(NULL);

  return device_list;
}

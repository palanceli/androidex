#ifndef _HELLO_ANDROID_H_
#define _HELLO_ANDROID_H_

#include <linux/cdev.h>
#include <linux/semaphore.h>

#define HA_DEVICE_NODE_NAME   "ha"
#define HA_DEVICE_FILE_NAME   "ha"
#define HA_DEVICE_PROC_NAME   "ha"
#define HA_DEVICE_CLASS_NAME  "ha"

struct hello_android_dev{
  int value;
  struct semaphore sem;
  struct cdev dev;
};

#endif

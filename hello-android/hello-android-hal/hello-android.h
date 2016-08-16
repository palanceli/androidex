#ifndef ANDROID_HA_INTERFACE_H
#define ANDROID_HA_INTERFACE_H

#include <hardware/hardware.h>

__BEGIN_DECLS

// 定义模块ID
#define HA_HARDWARE_MODULE_ID	"ha"

// 定义设备ID
#define HA_HARDWARE_DEVICE_ID	"ha"

// 自定义模块结构体
struct ha_module_t {
	struct hw_module_t common;
};

// 自定义设备结构体
struct ha_device_t{
	struct hw_device_t common;
	int fd;
	int (*set_value)(struct ha_device_t* dev, int value);
	int (*get_value)(struct ha_device_t* dev, int* value);
};

__END_DECLS

#endif
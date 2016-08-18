#define LOG_TAG	"haHALStub"

#include <hardware/hardware.h>
#include <hardware/hello-android.h>

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <cutils/log.h>
#include <cutils/atomic.h>

#define DEVICE_NAME		"/dev/ha"
#define MODULE_NAME		"ha"
#define MODULE_AUTHOR	"palanceli@163.com"

// 设备打开和关闭接口
static int ha_device_open(const struct hw_module_t* module, const char* id, struct hw_device_t** device);
static int ha_device_close(struct hw_device_t* device);

// 设备寄存器读写接口
static int ha_get_value(struct ha_device_t* dev, int* value);
static int ha_set_value(struct ha_device_t* dev, int value);

// 定义模块操作方法结构体变量
static struct hw_module_methods_t ha_module_methods = {
	open: ha_device_open
};

// 定义模块结构体变量
struct ha_module_t HAL_MODULE_INFO_SYM = {
	common: {
		tag 			: HARDWARE_MODULE_TAG,
		version_major	: 1,
		version_minor	: 0,
		id 				: HA_HARDWARE_MODULE_ID,
		name 			: MODULE_NAME,
		author 			: MODULE_AUTHOR,
		methods 		: &ha_module_methods,
		dso 			: NULL,
		reserved 		: {0},
	}
};

static int ha_device_open(const struct hw_module_t* module, const char* id, struct hw_device_t** device){
	if(!strcmp(id, HA_HARDWARE_MODULE_ID)){
		struct ha_device_t* dev;

		dev = (struct ha_device_t*)malloc(sizeof(struct ha_device_t));
		if(!dev){
			ALOGE("Failed to alloc space for freg_device_t.");
			return -EFAULT;
		}

		memset(dev, 0, sizeof(struct ha_device_t));

		dev->common.tag = HARDWARE_MODULE_TAG;
		dev->common.version = 0;
		dev->common.module = (hw_module_t*)module;
		dev->common.close = ha_device_close;
		dev->set_value = ha_set_value;
		dev->get_value = ha_get_value;

		if((dev->fd = open(DEVICE_NAME, O_RDWR)) == -1){
			ALOGE("Failed to open device file /dev/ha -- %s.", strerror(errno));
			free(dev);
			return -EFAULT;
		}

		*device = &(dev->common);

		ALOGI("Open device file /dev/ha successfully.");

		return 0;
	}
	return -EFAULT;
}

static int ha_device_close(struct hw_device_t* device){
	struct ha_device_t* ha_device = (struct ha_device_t*)device;
	if(ha_device){
		close(ha_device->fd);
		free(ha_device);
	}
	return 0;
}

static int ha_get_value(struct ha_device_t* dev, int* value){
	if(!dev){
		ALOGE("Null dev pointer.");
		return -EFAULT;
	}

	if(!value){
		ALOGE("Null value pointer.");
		return -EFAULT;
	}

	read(dev->fd, value, sizeof(*value));

	ALOGI("Get value %d from device file /dev/ha.", *value);

	return 0;
}

static int ha_set_value(struct ha_device_t* dev, int value){
	if(!dev){
		ALOGE("Null dev pointer.");
		return -EFAULT;
	}

	ALOGI("Set value %d to device file /dev/ha.", value);
	write(dev->fd, &value, sizeof(value));

	return 0;
}


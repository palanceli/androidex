#define LOG_TAG 	"HAServiceJNI"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>
#include <hardware/hardware.h>
#include <hardware/hello-android.h>

#include <stdio.h>

namespace android
{
	// 设置虚拟硬件设备ha的寄存器的值
	static void ha_setValue(JNIEnv* env, jobject clazz, jint ptr, jint value){
		// 将参数ptr转换为ha_device_t 结构体变量
		ha_device_t* device = (ha_device_t*)ptr;
		if(!device){
			LOGE("Device ha is not open.");
			return;
		}

		LOGI("Set value %d to device ha", value);
		device->set_value(device, value);
	}

	// 读取虚拟硬件设备HA的寄存器值
	static jint ha_getValue(JNIEnv* env, jobject clazz, jint ptr){
		// 将参数ptr转换为ha_device_t 结构体变量
		ha_device_t* device = (ha_device_t*)ptr;
		if(!device){
			LOGE("Device ha is not open.");
			return 0;
		}

		int value = 0;
		device->get_value(device, &value);

		LOGI("Get value %d from device ha.", value);

		return value;
	}

	// 打开虚拟硬件设备ha
	static inline int ha_device_open(const hw_module_t* module, struct ha_device_t** device){
		return module->methods->open(module, HA_HARDWARE_DEVICE_ID, (struct hw_device_t**)device);
	}

	// 初始化虚拟硬件设备ha
	static jint ha_init(JNIEnv* env, jclass clazz){
		ha_module_t* module;
		ha_device_t* device;

		LOGI("Initializing HAL stub ha ...");

		// 加载硬件抽象层模块ha
		if(hw_get_module(HA_HARDWARE_MODULE_ID, (const struct hw_module_t**)&module) == 0){
			LOGI("Device ha found.");
			// 打开虚拟硬件设备ha
			if(ha_device_open(&(module->common), &device) == 0){
				LOGI("Device ha is open.");
				// 将ha_device_t借口转换为整型值返回
				return (jint)device;
			}
			LOGE("Failed to open device ha.");
			return 0;
		}
		LOGE("Failed to get HAL stub ha.");
		return 0;
	}

	// JAVA本地接口方法表
	static const JNINativeMethod method_table[] = {
		{"init_native", "()I", (void*)ha_init},
		{"setValue_native", "(II)V", (void*)ha_setValue},
		{"getValue_native", "(I)I", (void*)ha_getValue},
	}

	// 注册Java本地接口方法
	int register_android_server_HAService(JNIEnv* env){
		return jniRegisterNativeMethods(env, "com/android/server/HaService", 
			method_table, NELEM(method_table));
	}
};
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
	}
};
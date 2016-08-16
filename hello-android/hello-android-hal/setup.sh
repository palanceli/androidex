scriptPath=$(cd "$(dirname "$0")"; pwd)
if [ ! -L "$scriptPath/../../../android-6.0.1_r11/hardware/libhardware/include/hardware/hello-android.h" ]; then
	echo "创建软链接 android-6.0.1_r11/hardware/libhardware/include/hardware/hello-android.h --> $scriptPath/hello-android.h"
	ln -s $scriptPath/hello-android.h $scriptPath/../../../android-6.0.1_r11/hardware/libhardware/include/hardware/hello-android.h
fi

if [ ! -L "$scriptPath/../../../android-6.0.1_r11/hardware/libhardware/modules/hello-android" ]; then
	echo "创建软链接 android-6.0.1_r11/hardware/libhardware/modules/hello-android --> $scriptPath"
	ln -s $scriptPath $scriptPath/../../../android-6.0.1_r11/hardware/libhardware/modules/hello-android
fi
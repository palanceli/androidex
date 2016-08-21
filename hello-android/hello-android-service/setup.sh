scriptPath=$(cd "$(dirname "$0")"; pwd)
if [ ! -L "$scriptPath/../../../android-6.0.1_r11/frameworks/base/core/java/android/os/IHAService.aidl" ]; then
	echo "创建软链接 android-6.0.1_r11/frameworks/base/core/java/android/os/IHAService.aidl --> $scriptPath/IHAService.aidl"
	ln -s $scriptPath/IHAService.aidl $scriptPath/../../../android-6.0.1_r11/frameworks/base/core/java/android/os/IHAService.aidl
fi

if [ ! -L "$scriptPath/../../../android-6.0.1_r11/frameworks/base/services/java/com/android/server/HAService.java" ]; then
	echo "创建软链接 android-6.0.1_r11/frameworks/base/services/java/com/android/server/HAService.java --> $scriptPath/HAService.java"
	ln -s $scriptPath/HAService.java $scriptPath/../../../android-6.0.1_r11/frameworks/base/services/java/com/android/server/HAService.java
fi

if [ ! -L "$scriptPath/../../../android-6.0.1_r11/frameworks/base/services/core/jni/com_android_server_HAService.cpp" ]; then
	echo "创建软链接 android-6.0.1_r11/frameworks/base/services/core/jni/com_android_server_HAService.cpp --> $scriptPath/com_android_server_HAService.cpp"
	ln -s $scriptPath/com_android_server_HAService.cpp $scriptPath/../../../android-6.0.1_r11/frameworks/base/services/core/jni/com_android_server_HAService.cpp
fi
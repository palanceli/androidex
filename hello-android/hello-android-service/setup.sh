scriptPath=$(cd "$(dirname "$0")"; pwd)
if [ ! -L "$scriptPath/../../../android-6.0.1_r11/frameworks/base/core/java/android/os/IHAService.aidl" ]; then
	echo "创建软链接 android-6.0.1_r11/frameworks/base/core/java/android/os/IHAService.aidl --> $scriptPath/IHAService.aidl"
	ln -s $scriptPath/IHAService.aidl $scriptPath/../../../android-6.0.1_r11/frameworks/base/core/java/android/os/IHAService.aidl
fi


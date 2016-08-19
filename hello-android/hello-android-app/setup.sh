scriptPath=$(cd "$(dirname "$0")"; pwd)
if [ ! -L "$scriptPath/../../../android-6.0.1_r11/packages/experimental/HelloAndroid" ]; then
	echo "创建软链接 android-6.0.1_r11/packages/experimental/HelloAndroid --> $scriptPath"
	ln -s $scriptPath $scriptPath/../../../android-6.0.1_r11/packages/experimental/HelloAndroid
fi
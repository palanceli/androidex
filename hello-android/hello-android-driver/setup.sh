#!/bin/bash
scriptPath=$(cd "$(dirname "$0")"; pwd)

if [ ! -L "$scriptPath/../../../android-6.0.1_r11/kernel/goldfish/drivers/hello-android" ]; then
	echo "创建软链接 android-6.0.1_r11/kernel/goldfish/drivers/hello-android --> $scriptPath"
	ln -s $scriptPath $scriptPath/../../../android-6.0.1_r11/kernel/goldfish/drivers/hello-android
fi


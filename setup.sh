#!/bin/bash

#sh drivers-freg/setup.sh
#sh external-freg/setup.sh
#sh external-testlog/setup.sh
#sh libhardware-freg/setup.sh
#sh external-helloworld/setup.sh
#sh external-testservice/setup.sh

#sh hello-android/hello-android-driver/setup.sh $*
#sh hello-android/ha-driver-checker/setup.sh $*
#sh hello-android/hello-android-hal/setup.sh $*
#sh hello-android/hello-android-service/setup.sh $*
#sh hello-android/hello-android-app/setup.sh $*

python hello-android/hello-android-driver/setup.py $*
python hello-android/ha-driver-checker/setup.py $*
python hello-android/hello-android-hal/setup.py $*
python hello-android/hello-android-service/setup.py $*
#python hello-android/hello-android-app/setup.py $*
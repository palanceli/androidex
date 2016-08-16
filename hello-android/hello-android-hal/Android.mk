LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw	# 编译出的动态链接库文件的保存目录，
														# 即out/target/product/generic/system/lib/hw
LOCAL_SHARED_LIBRARIES := liblog
LOCAL_SRC_FILES := hello-android.cpp
LOCAL_MODULE := hello-android.default	# 该动态链接库的名称为hello-android.default
include $(BUILD_SHARED_LIBRARY)			# 表示将该硬件抽象层模块编译成一个动态链接库文件

# 编译成功后，系统会自动在hello-android.default后面追加.so即hello-android.default.so

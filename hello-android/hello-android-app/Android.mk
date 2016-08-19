LOCAL_PATH:= $(call my-dir)
inclue $(CLEAR_VARS)
LOCAL_MODULE_TAGS:=optional
LOCAL_SRC_FILES := $(call all-subdir-java-files)
LOCAL_PACKAGE_NAME := Ha
include $(BUILD_PACKAGE)

package com.android.server;

import android.content.Context;
import android.os.IHAService;
import android.util.Slog;

public class HAService extends IHAService.Stub {
	private static final String TAG = "HAService";
	private int mPtr = 0;

	HAService(){
		mPtr = init_native();

		if(mPtr == 0){
			Slog.e(TAG, "Failed to initialize HA service.");
			return;
		}
	}

	public void setValue(int value){
		if(mPtr == 0){
			Slog.e(TAG, "HA service is not initialized.");
			return;
		}
		setValue_native(mPtr, value);
	}

	public int getValue(){
		if(mPtr == 0){
			Slog.e(TAG, "HA service is not initialized.");
			return 0;
		}
		return getValue_native(mPtr);
	}

	private static native int init_native();
	private static native void setValue_native(int ptr, int value);
	private static native int getValue_native(int ptr);
};
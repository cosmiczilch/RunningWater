package com.vajra.examplegame;

import android.content.Context;

public class ExampleGame2Wrapper {

	public static void SetContext(Context context) {
		ExampleGame2Wrapper.savedContext = context;
	}
	
	public static Context GetContext() {
		return ExampleGame2Wrapper.savedContext;
	}
	
	static {
		System.loadLibrary("ExampleGame2");
	}
	
	private static Context savedContext;

	public static native void InitGameScene();
}

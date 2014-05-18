package com.vajra.examplegame;

import android.content.Context;

public class ExampleGame3Wrapper {

	public static void SetContext(Context context) {
		ExampleGame3Wrapper.savedContext = context;
	}
	
	public static Context GetContext() {
		return ExampleGame3Wrapper.savedContext;
	}
	
	static {
		System.loadLibrary("ExampleGame3");
	}
	
	private static Context savedContext;

	public static native void InitGameScene();
}

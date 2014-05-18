#ifdef PLATFORM_ANDROID

#include "ExampleGame3/AndroidWrapper/AndroidWrapper.h"
#include "ExampleGame3/Test/TestFile.h"

JNIEXPORT void JNICALL Java_com_vajra_examplegame_ExampleGame3Wrapper_InitGameScene(JNIEnv * env, jobject obj) {
	TestFuntion();
}

#endif // PLATFORM_ANDROID


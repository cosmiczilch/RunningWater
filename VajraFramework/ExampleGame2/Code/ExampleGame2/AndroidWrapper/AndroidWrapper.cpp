#ifdef PLATFORM_ANDROID

#include "ExampleGame2/AndroidWrapper/AndroidWrapper.h"
#include "ExampleGame2/Test/TestFile.h"

JNIEXPORT void JNICALL Java_com_vajra_examplegame_ExampleGame2Wrapper_InitGameScene(JNIEnv * env, jobject obj) {
	TestFuntion();
}

#endif // PLATFORM_ANDROID


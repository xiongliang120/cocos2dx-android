#include "JniCallback.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, __FILE__, __VA_ARGS__)
#else
#define LOGI(...) ;
#endif

extern "C" {
JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_AppActivity_NativeFunShowText(JNIEnv *env, jclass method, jstring param) {
    char *data = (char *) env->GetStringUTFChars(param, NULL);
    LOGI("msg java 调用 C++ 了");
    env->ReleaseStringUTFChars(param, data);
}
}




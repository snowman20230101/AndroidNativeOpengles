#include "CommonInclude.h"
#include "GLRenderContext.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_windy_opengles_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_windy_opengles_render_NativeRender_native_1init(JNIEnv *env, jobject thiz) {
    GLRenderContext::getInstance();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_windy_opengles_render_NativeRender_native_1unInit(JNIEnv *env, jobject thiz) {
    GLRenderContext::destroyInstance();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_windy_opengles_render_NativeRender_native_1onSurfaceCreated(JNIEnv *env, jobject thiz) {
    GLRenderContext::getInstance()->onSurfaceCreated();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_windy_opengles_render_NativeRender_native_1onSurfaceChanged(JNIEnv *env, jobject thiz,
                                                                     jint width, jint height) {
    GLRenderContext::getInstance()->onSurfaceChanged(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_windy_opengles_render_NativeRender_native_1onDrawFrame(JNIEnv *env, jobject thiz) {
    GLRenderContext::getInstance()->onDrawFrame();
}
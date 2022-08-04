#include "CommonInclude.h"
#include "GLRenderContext.h"
#include "CallJavaHelper.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_windy_opengles_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
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

extern "C"
JNIEXPORT void JNICALL
Java_com_windy_opengles_render_NativeRender_native_1setImageData(JNIEnv *env, jobject thiz,
                                                                 jint format, jint width,
                                                                 jint height,
                                                                 jbyteArray imageData) {
    int len = env->GetArrayLength(imageData);
    uint8_t *buf = new uint8_t[len];
    env->GetByteArrayRegion(imageData, 0, len, reinterpret_cast<jbyte *>(buf));
    GLRenderContext::getInstance()->setImageData(format, width, height, buf);
    delete[] buf;
    env->DeleteLocalRef(imageData);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_windy_opengles_render_NativeRender_native_1setImageDataWithIndex(JNIEnv *env, jobject thiz,
                                                                          jint index, jint format,
                                                                          jint width, jint height,
                                                                          jbyteArray imageData) {
    int len = env->GetArrayLength(imageData);
    uint8_t *buf = new uint8_t[len];
    env->GetByteArrayRegion(imageData, 0, len, reinterpret_cast<jbyte *>(buf));
    GLRenderContext::getInstance()->setImageDataWithIndex(index, format, width, height, buf);
    delete[] buf;
    env->DeleteLocalRef(imageData);
}
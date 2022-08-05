#include "CommonInclude.h"
#include "GLRenderContext.h"
#include "CallJavaHelper.h"

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

extern "C"
JNIEXPORT void JNICALL
Java_com_windy_opengles_render_NativeRender_native_1setParamsFloat(JNIEnv *env, jobject thiz,
                                                                   jint param_type, jfloat value0,
                                                                   jfloat value1) {
    GLRenderContext::getInstance()->setParamsFloat(param_type, value0, value1);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_windy_opengles_render_NativeRender_native_1setParamsInt(JNIEnv *env, jobject thiz,
                                                                 jint param_type, jint value0,
                                                                 jint value1) {
    GLRenderContext::getInstance()->setParamsInt(param_type, value0, value1);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_windy_opengles_render_NativeRender_native_1setAudioData(JNIEnv *env, jobject thiz,
                                                                 jshortArray audio_data) {
    jsize len = env->GetArrayLength(audio_data);
    short *pShortBuf = new short[len];
    env->GetShortArrayRegion(audio_data, 0, len, pShortBuf);
    GLRenderContext::getInstance()->setParamsShortArr(pShortBuf, len);
    delete[] pShortBuf;
    env->DeleteLocalRef(audio_data);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_windy_opengles_render_NativeRender_native_1updateTransformMatrix(JNIEnv *env, jobject thiz,
                                                                          jfloat rotate_x,
                                                                          jfloat rotate_y,
                                                                          jfloat scale_x,
                                                                          jfloat scale_y) {
    GLRenderContext::getInstance()->updateTransformMatrix(rotate_x, rotate_y, scale_x, scale_y);
}
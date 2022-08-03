//
// Created by windy on 2022/8/2.
//

#ifndef ANDROIDNATIVEOPENGLES_COMMONINCLUDE_H
#define ANDROIDNATIVEOPENGLES_COMMONINCLUDE_H

// android 头文件
#include <jni.h>
#include <android/log.h>
#include <sys/time.h>

// 标准库
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cassert>
#include <thread>

#include <malloc.h>

// openGL 数学
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// opengl native 头文件
//#include <GLES2/gl2.h>
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>

// 日志系统
#define TAG_FFMPEG "NATIVE-GLES"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG_FFMPEG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG_FFMPEG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG_FFMPEG, __VA_ARGS__)

#define FUN_BEGIN_TIME(FUN) {\
    LOGE("%s:%s func start", __FILE__, FUN); \
    long long t0 = GetSysCurrentTime();

#define FUN_END_TIME(FUN) \
    long long t1 = GetSysCurrentTime(); \
    LOGE("%s:%s func cost time %ldms", __FILE__, FUN, (long)(t1-t0));}

#define BEGIN_TIME(FUN) {\
    LOGE("%s func start", FUN); \
    long long t0 = GetSysCurrentTime();

#define END_TIME(FUN) \
    long long t1 = GetSysCurrentTime(); \
    LOGE("%s func cost time %ldms", FUN, (long)(t1-t0));}

#define GO_CHECK_GL_ERROR(...)  LOGE("CHECK_GL_ERROR %s glGetError = %d, line = %d, ",  __FUNCTION__, glGetError(), __LINE__)

#define DEBUG_LOGCATE(...)  LOGE("DEBUG_LOGCATE %s line = %d",  __FUNCTION__, __LINE__)

static long long GetSysCurrentTime() {
    struct timeval time;
    gettimeofday(&time, NULL);
    long long curTime = ((long long) (time.tv_sec)) * 1000 + time.tv_usec / 1000;
    return curTime;
}


class CommonInclude {

};


#endif //ANDROIDNATIVEOPENGLES_COMMONINCLUDE_H

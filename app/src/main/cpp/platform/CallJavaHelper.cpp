//
// Created by windy on 2022/8/3.
//

#include "CallJavaHelper.h"

/**
 * jvm 引用
 */
JavaVM *CallJavaHelper::_psJavaVM = nullptr;
jmethodID CallJavaHelper::loadClassMethod_methodID = nullptr;
jobject CallJavaHelper::classloader = nullptr;

/**
 * 加载类加载器，回调函数
 */
std::function<void()> CallJavaHelper::classloaderCallback = nullptr;

// pthread key
static pthread_key_t g_key;

/**
 * env 线程回调
 *
 * @param args
 */
void _detachCurrentThread(void *args);

/**
 * jni 找类字节码对象指针ID
 *
 * @param className
 * @return
 */
jclass _getClassID(const char *className);

void CallJavaHelper::setJavaVM(JavaVM *javaVM) {
    pthread_t thisThread = pthread_self();

    LOGD("JniHelper::setJavaVM(%p), pthread_self() = %ld", javaVM, thisThread);

    _psJavaVM = javaVM;
    pthread_key_create(&g_key, _detachCurrentThread);
}

JavaVM *CallJavaHelper::getJavaVM() {
    pthread_t thisThread = pthread_self();

    LOGD("JniHelper::getJavaVM(), pthread_self() = %ld", thisThread);

    return _psJavaVM;
}

JNIEnv *CallJavaHelper::cacheEnv(JavaVM *jvm) {
    JNIEnv *_env = nullptr;
    // get jni environment
    jint ret = jvm->GetEnv((void **) &_env, JNI_VERSION_1_4);

    switch (ret) {
        case JNI_OK :
            // Success!
            pthread_setspecific(g_key, _env);
            return _env;

        case JNI_EDETACHED :
            // Thread not attached
            if (jvm->AttachCurrentThread(&_env, nullptr) < 0) {
                LOGE("Failed to get the environment using AttachCurrentThread()");

                return nullptr;
            } else {
                // Success : Attached and obtained JNIEnv!
                pthread_setspecific(g_key, _env);
                return _env;
            }
        case JNI_EVERSION :
            // Cannot recover from this error
            LOGE("JNI interface version 1.4 not supported");
        default :
            LOGE("Failed to get the environment using GetEnv()");
            return nullptr;
    }
}

JNIEnv *CallJavaHelper::getEnv() {
    JNIEnv *_env = (JNIEnv *) pthread_getspecific(g_key);
    if (_env == nullptr)
        _env = CallJavaHelper::cacheEnv(_psJavaVM);
    return _env;
}

bool CallJavaHelper::getStaticMethodInfo(JniMethodInfo &methodInfo, const char *className,
                                         const char *methodName, const char *paramCode) {
    if ((nullptr == className) ||
        (nullptr == methodName) ||
        (nullptr == paramCode)) {
        return false;
    }

    JNIEnv *env = CallJavaHelper::getEnv();
    if (!env) {
        LOGE("Failed to get JNIEnv");
        return false;
    }

    jclass classID = _getClassID(className);
    if (!classID) {
        LOGE("Failed to find class %s", className);
        env->ExceptionClear();
        return false;
    }

    jmethodID methodID = env->GetStaticMethodID(classID, methodName, paramCode);
    if (!methodID) {
        LOGE("Failed to find static method id of %s", methodName);
        env->ExceptionClear();
        return false;
    }

    methodInfo.classID = classID;
    methodInfo.env = env;
    methodInfo.methodID = methodID;

    return true;
}

bool CallJavaHelper::getMethodInfo(JniMethodInfo &methodInfo, const char *className,
                                   const char *methodName, const char *paramCode) {
    if ((nullptr == className) ||
        (nullptr == methodName) ||
        (nullptr == paramCode)) {
        return false;
    }

    JNIEnv *env = CallJavaHelper::getEnv();
    if (!env) {
        LOGE("Failed to get JNIEnv");
        return false;
    }

    jclass classID = _getClassID(className);
    if (!classID) {
        LOGE("Failed to find class %s", className);
        env->ExceptionClear();
        return false;
    }

    jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
    if (!methodID) {
        LOGE("Failed to find static method id of %s", methodName);
        env->ExceptionClear();
        return false;
    }

    methodInfo.classID = classID;
    methodInfo.env = env;
    methodInfo.methodID = methodID;

    return true;
}

bool CallJavaHelper::getMethodInfo_DefaultClassLoader(JniMethodInfo &methodInfo,
                                                      const char *className,
                                                      const char *methodName,
                                                      const char *paramCode) {
    if ((nullptr == className) ||
        (nullptr == methodName) ||
        (nullptr == paramCode)) {
        return false;
    }

    JNIEnv *env = CallJavaHelper::getEnv();
    if (!env) {
        LOGE("Failed to get JNIEnv");
        return false;
    }

    jclass classID = env->FindClass(className);
    if (!classID) {
        LOGE("Failed to find class %s", className);
        env->ExceptionClear();
        return false;
    }

    jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
    if (!methodID) {
        LOGE("Failed to find method id of %s", methodName);
        env->ExceptionClear();
        return false;
    }

    methodInfo.classID = classID;
    methodInfo.env = env;
    methodInfo.methodID = methodID;
    return true;
}

std::string CallJavaHelper::jString2string(jstring jstr) {
    if (jstr == nullptr) {
        return "";
    }

    JNIEnv *env = CallJavaHelper::getEnv();
    if (!env) {
        return "";
    }

    std::string strValue = StringUtils::getStringUTFCharsJNI(env, jstr);

    return strValue;
}

bool CallJavaHelper::setClassLoaderFrom(jobject activityInstance) {
    JniMethodInfo _androidClassLoaderMethod;
    // 1. 找到类加载器函数指针
    if (!CallJavaHelper::getMethodInfo_DefaultClassLoader(_androidClassLoaderMethod,
                                                          "android/content/Context",
                                                          "getClassLoader",
                                                          "()Ljava/lang/ClassLoader;")) {
        return false;
    }

    JNIEnv *env = CallJavaHelper::getEnv();
    if (!env) {
        LOGE("Failed to get JNIEnv");
        return false;
    }

    // 2. 执行函数
    jobject obj = env->CallObjectMethod(activityInstance, _androidClassLoaderMethod.methodID);
    if (obj == nullptr) {
        return false;
    }

    // 3. 找到自定义类加载方法
    JniMethodInfo _m;
    if (!CallJavaHelper::getMethodInfo_DefaultClassLoader(_m,
                                                          "java/lang/ClassLoader",
                                                          "loadClass",
                                                          "(Ljava/lang/String;)Ljava/lang/Class;")) {
        return false;
    }

    // 4. 全局本地化
    CallJavaHelper::classloader = env->NewGlobalRef(obj);

    // 5. 记录方法
    CallJavaHelper::loadClassMethod_methodID = _m.methodID;

    if (classloaderCallback != nullptr) {
        classloaderCallback();
    }

    return true;
}

void CallJavaHelper::reportError(const std::string &className, const std::string &methodName,
                                 const std::string &signature) {
    LOGE("Failed to find static java method. Class name: %s, method name: %s, signature: %s ",
         className.c_str(), methodName.c_str(), signature.c_str());
}

void CallJavaHelper::deleteLocalRefs(JNIEnv *env, CallJavaHelper::LocalRefMapType &localRefs) {
    if (!env) {
        return;
    }

    for (const jobject &ref: localRefs[env]) {
        env->DeleteLocalRef(ref);
    }
    localRefs[env].clear();
}

jstring CallJavaHelper::convert(CallJavaHelper::LocalRefMapType &localRefs, JniMethodInfo &t,
                                const char *x) {
    jstring ret = StringUtils::newStringUTFJNI(t.env, x ? x : "");
    localRefs[t.env].push_back(ret);
    return ret;
}

jstring CallJavaHelper::convert(CallJavaHelper::LocalRefMapType &localRefs, JniMethodInfo &t,
                                const std::string &x) {
    return convert(localRefs, t, x.c_str());
}

jclass _getClassID(const char *className) {
    if (nullptr == className) {
        return nullptr;
    }

    JNIEnv *env = CallJavaHelper::getEnv();
    if (!env) {
        LOGE("Failed to get JNIEnv");
        return nullptr;
    }

    jstring _jstrClassName = env->NewStringUTF(className);

    jclass _clazz = (jclass) env->CallObjectMethod(CallJavaHelper::classloader,
                                                   CallJavaHelper::loadClassMethod_methodID,
                                                   _jstrClassName);

    if (_clazz == nullptr) {
        LOGE("Classloader failed to find class of %s", className);
        env->ExceptionClear();
    }

    env->DeleteLocalRef(_jstrClassName);

    return _clazz;
}

void _detachCurrentThread(void *args) {
    CallJavaHelper::getJavaVM()->DetachCurrentThread();
}
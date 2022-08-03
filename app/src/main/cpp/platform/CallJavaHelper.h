//
// Created by windy on 2022/8/3.
//

#ifndef ANDROIDNATIVEOPENGLES_CALLJAVAHELPER_H
#define ANDROIDNATIVEOPENGLES_CALLJAVAHELPER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include "CommonInclude.h"
#include "ConvertUTF.h"
#include "ccUTF8.h"

typedef struct JniMethodInfo_ {
    JNIEnv *env;
    jclass classID; // 字节码对象
    jmethodID methodID; // 函数对象
} JniMethodInfo;

class CallJavaHelper {
public:

    /**
     * 自定义map
     */
    typedef std::unordered_map<JNIEnv *, std::vector<jobject>> LocalRefMapType;
public:
    /**
     * 设置类加载器
     *
     * @param activityInstance
     * @return
     */
    static bool setClassLoaderFrom(jobject activityInstance);

    /**
     * JavaVM 对象
     *
     * @param javaVM
     */
    static void setJavaVM(JavaVM *javaVM);

    static JavaVM *getJavaVM();

    /**
     * JNIEnv 环境
     *
     * @return
     */
    static JNIEnv *getEnv();

    /**
     * 获取静态方法
     *
     * @param methodInfo
     * @param className
     * @param methodName
     * @param paramCode
     * @return
     */
    static bool getStaticMethodInfo(JniMethodInfo &methodInfo,
                                    const char *className,
                                    const char *methodName,
                                    const char *paramCode
    );

    /**
     * 获取普通方法
     *
     * @param methodInfo
     * @param className
     * @param methodName
     * @param paramCode
     * @return
     */
    static bool getMethodInfo(JniMethodInfo &methodInfo,
                              const char *className,
                              const char *methodName,
                              const char *paramCode
    );

    /**
     * 静态方法的调用
     *
     * @tparam Ts
     * @param className
     * @param methodName
     * @param xs
     */
    template<typename... Ts>
    static void callStaticVoidMethod(const std::string &className,
                                     const std::string &methodName,
                                     Ts... xs) {

        JniMethodInfo m;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")V";
        LOGD("callStaticVoidMethod() signature=%s", signature.c_str());
        if (!getStaticMethodInfo(m, className.c_str(), methodName.c_str(), signature.c_str())) {
            reportError(className, methodName, signature);
        }

        LocalRefMapType refMapType;
        m.env->CallStaticVoidMethod(m.classID, m.methodID, convert(refMapType, m, xs)...);
        m.env->DeleteLocalRef(m.classID);
        deleteLocalRefs(m.env, refMapType);
    };

    /**
     * 静态方法的调用
     *
     * @tparam Ts
     * @param className
     * @param methodName
     * @param xs
     * @return
     */
    template<typename... Ts>
    static std::string callStaticStringMethod(const std::string &className,
                                              const std::string &methodName,
                                              Ts... xs) {
        std::string ret;
        JniMethodInfo m;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")Ljava/lang/String;";
        LOGD("callStaticStringMethod() signature=%s", signature.c_str());
        if (!getStaticMethodInfo(m, className.c_str(), methodName.c_str(), signature.c_str())) {
            reportError(className, methodName, signature);
        }

        LocalRefMapType refMapType;
        jstring jStr = (jstring) m.env->CallStaticObjectMethod(m.classID, m.methodID,
                                                         convert(refMapType, m, xs)...);
        ret = jString2string(jStr);
        m.env->DeleteLocalRef(m.classID);
        m.env->DeleteLocalRef(jStr);
        deleteLocalRefs(m.env, refMapType);

        return ret;
    }

    static std::string jString2string(jstring str);

private:
    static JNIEnv *cacheEnv(JavaVM *jvm);

    /**
     * 获取Android 类加载器
     *
     * @param methodInfo
     * @param className
     * @param methodName
     * @param paramCode
     * @return
     */
    static bool getMethodInfo_DefaultClassLoader(JniMethodInfo &methodInfo,
                                                 const char *className,
                                                 const char *methodName,
                                                 const char *paramCode);

    /**
     * 打印日志
     *
     * @param className
     * @param methodName
     * @param signature
     */
    static void reportError(const std::string &className, const std::string &methodName,
                            const std::string &signature);

    static std::string getJNISignature() {
        return "";
    }

    static std::string getJNISignature(bool) {
        return "Z";
    }

    static std::string getJNISignature(char) {
        return "C";
    }

    static std::string getJNISignature(short) {
        return "S";
    }

    static std::string getJNISignature(int) {
        return "I";
    }

    static std::string getJNISignature(long) {
        return "J";
    }

    static std::string getJNISignature(float) {
        return "F";
    }

    static std::string getJNISignature(double) {
        return "D";
    }

    static std::string getJNISignature(const char *) {
        return "Ljava/lang/String;";
    }

    static std::string getJNISignature(const std::string &) {
        return "Ljava/lang/String;";
    }

    /**
     * 函数签名转换
     *
     * @tparam T
     * @tparam Ts
     * @param x
     * @param xs
     * @return
     */
    template<typename T, typename... Ts>
    static std::string getJNISignature(T x, Ts... xs) {
        return getJNISignature(x) + getJNISignature(xs...);
    }

    template<typename T>
    static std::string getJNISignature(T x) {
        // This template should never be instantiated
        static_assert(sizeof(x) == 0, "Unsupported argument type");
        return "";
    }

    /**
     * Map 转换泛型
     *
     * @tparam T
     * @param localRefs
     * @param x
     * @return
     */
    template<typename T>
    static T convert(LocalRefMapType &localRefs, JniMethodInfo &, T x) {
        return x;
    }

    static jstring convert(LocalRefMapType &localRefs,
                           JniMethodInfo &t, const char *x);

    static jstring convert(LocalRefMapType &localRefs,
                           JniMethodInfo &t, const std::string &x);

    inline static jint convert(LocalRefMapType &, JniMethodInfo &,
                               int32_t value) {
        return static_cast<jint>(value);
    }

    inline static jlong convert(LocalRefMapType &, JniMethodInfo &,
                                int64_t value) {
        return static_cast<jlong>(value);
    }

    inline static jfloat convert(LocalRefMapType &, JniMethodInfo &,
                                 float value) {
        return static_cast<jfloat>(value);
    }

    inline static jdouble convert(LocalRefMapType &, JniMethodInfo &,
                                  double value) {
        return static_cast<jdouble>(value);
    }

    inline static jboolean convert(LocalRefMapType &, JniMethodInfo &,
                                   bool value) {
        return static_cast<jboolean>(value);
    }

    inline static jbyte convert(LocalRefMapType &, JniMethodInfo &,
                                int8_t value) {
        return static_cast<jbyte>(value);
    }

    inline static jchar convert(LocalRefMapType &, JniMethodInfo &,
                                uint8_t value) {
        return static_cast<jchar>(value);
    }

    inline static jshort convert(LocalRefMapType &, JniMethodInfo &,
                                 int16_t value) {
        return static_cast<jshort>(value);
    }

    static void deleteLocalRefs(JNIEnv *env, LocalRefMapType &localRefs);

    static JavaVM *_psJavaVM;

public:
    /**
     * 当前类加载器，对象 和 new ClassLoader() 的产物一样
     */
    static jobject classloader;
    /**
     * 类加载器函数
     */
    static jmethodID loadClassMethod_methodID;
    static std::function<void()> classloaderCallback;
};


#endif //ANDROIDNATIVEOPENGLES_CALLJAVAHELPER_H

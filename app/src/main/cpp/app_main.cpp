//
// Created by windy on 2022/8/3.
//

#ifndef ANDROIDNATIVEOPENGLES_APP_MAIN_CPP
#define ANDROIDNATIVEOPENGLES_APP_MAIN_CPP

#include "CommonInclude.h"
#include "CallJavaHelper.h"
#include "ResourceManager.h"


JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    CallJavaHelper::setJavaVM(vm);
    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_windy_opengles_MainActivity_nativeSetContext(JNIEnv *env, jobject thiz, jobject context,
                                                      jobject asset_manager) {
    CallJavaHelper::setClassLoaderFrom(context);
    AAssetManager *assetManager = AAssetManager_fromJava(env, asset_manager);
    ResourceManager::getInstance()->setAssetManager(assetManager);
}

#endif //ANDROIDNATIVEOPENGLES_APP_MAIN_CPP


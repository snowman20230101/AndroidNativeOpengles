//
// Created by windy on 2022/8/3.
//

#include "ResourceManager.h"

ResourceManager *ResourceManager::instance = nullptr;
//AAssetManager *ResourceManager::assetManager = nullptr;

static const std::string className = "com.windy.opengles.util.ShaderUtil";

ResourceManager::ResourceManager() {
    LOGD("ResourceManager::ResourceManager");
}

ResourceManager::~ResourceManager() {
    LOGD("ResourceManager::~ResourceManager");
}

ResourceManager *ResourceManager::getInstance() {
    if (instance == nullptr) {
        instance = new ResourceManager();
    }
    return instance;
}

std::string ResourceManager::getShader2Triangle() {
    std::string res = CallJavaHelper::callStaticStringMethod(className, "getTriangleVertSrr");
    return res;
}

void ResourceManager::setAssetManager(AAssetManager *manager) {
    if (manager == nullptr) {
        LOGE("setAssetManager : received unexpected nullptr parameter");
        return;
    }
    this->assetManager = manager;
}

/**
 * TODO 这个函数会内存泄漏
 *
 * @param fileName
 * @return
 */
const char *ResourceManager::getShaderSource(const char *fileName) {
    AAsset *asset = AAssetManager_open(assetManager, fileName, AASSET_MODE_UNKNOWN);
    off_t len = AAsset_getLength(asset);
    char *buffer = static_cast<char *>(malloc(sizeof(char *) + len + 1));
    buffer[len] = '\0';
    AAsset_read(asset, buffer, len);
    AAsset_close(asset);
    return buffer;
}

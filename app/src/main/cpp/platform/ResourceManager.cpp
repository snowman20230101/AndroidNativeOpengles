//
// Created by windy on 2022/8/3.
//

#include "ResourceManager.h"

ResourceManager *ResourceManager::instance = nullptr;

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

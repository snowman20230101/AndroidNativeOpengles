
//
// Created by windy on 2022/8/3.
//

#ifndef ANDROIDNATIVEOPENGLES_RESOURCEMANAGER_H
#define ANDROIDNATIVEOPENGLES_RESOURCEMANAGER_H

#include "CommonInclude.h"
#include "CallJavaHelper.h"

class ResourceManager {
public:
    static ResourceManager *getInstance();

    std::string getShader2Triangle();

    const char *getShaderSource(const char *fileName);

    void setAssetManager(AAssetManager *manager);

private:
    ResourceManager();

    ~ResourceManager();

    static ResourceManager *instance;

    AAssetManager *assetManager = nullptr;
};


#endif //ANDROIDNATIVEOPENGLES_RESOURCEMANAGER_H

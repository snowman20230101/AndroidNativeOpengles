
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

private:
    ResourceManager();

    ~ResourceManager();

    static ResourceManager *instance;
};


#endif //ANDROIDNATIVEOPENGLES_RESOURCEMANAGER_H

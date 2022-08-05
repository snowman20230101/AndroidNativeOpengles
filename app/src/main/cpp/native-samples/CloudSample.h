//
// Created by windy on 2022/8/5.
//

#ifndef ANDROIDNATIVEOPENGLES_CLOUDSAMPLE_H
#define ANDROIDNATIVEOPENGLES_CLOUDSAMPLE_H

#include "CommonInclude.h"
#include "GLSampleBase.h"
#include "ResourceManager.h"


class CloudSample : public GLSampleBase {
public:
    CloudSample();
    ~CloudSample();

    virtual void init();

    virtual void draw(int screenW, int screenH);

    virtual void destroy();
};


#endif //ANDROIDNATIVEOPENGLES_CLOUDSAMPLE_H

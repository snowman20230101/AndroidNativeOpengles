//
// Created by windy on 2022/8/2.
//

#ifndef ANDROIDNATIVEOPENGLES_TRIANGLESAMPLE_H
#define ANDROIDNATIVEOPENGLES_TRIANGLESAMPLE_H


#include <ImageDef.h>
#include "GLSampleBase.h"

class TriangleSample : public GLSampleBase {

public:
    TriangleSample();

    ~TriangleSample();

    virtual void loadImage(NativeImage *pImage);

    virtual void init();

    virtual void draw(int screenW, int screenH);

    virtual void destroy();
};


#endif //ANDROIDNATIVEOPENGLES_TRIANGLESAMPLE_H

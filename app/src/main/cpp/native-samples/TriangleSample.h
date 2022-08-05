//
// Created by windy on 2022/8/2.
//

#ifndef ANDROIDNATIVEOPENGLES_TRIANGLESAMPLE_H
#define ANDROIDNATIVEOPENGLES_TRIANGLESAMPLE_H


#include "ImageDef.h"
#include "GLSampleBase.h"

class TriangleSample : public GLSampleBase {

public:
    TriangleSample();

    ~TriangleSample() override;

    virtual void loadImage(NativeImage *pImage) override;

    virtual void init() override;

    virtual void draw(int screenW, int screenH) override;

    virtual void destroy() override;

private:
    GLfloat vVertices[9] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };
};


#endif //ANDROIDNATIVEOPENGLES_TRIANGLESAMPLE_H

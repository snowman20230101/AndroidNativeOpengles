//
// Created by windy on 2022/8/2.
//

#ifndef ANDROIDNATIVEOPENGLES_GLSAMPLEBASE_H
#define ANDROIDNATIVEOPENGLES_GLSAMPLEBASE_H

#include <ImageDef.h>
#include "CommonInclude.h"

class GLSampleBase {
public:
    GLSampleBase() {
        m_vertexShader = 0;
        m_fragmentShader = 0;
        m_programObj = 0;
        m_surfaceWidth = 0;
        m_surfaceHeight = 0;
    };

    /**
     * 析构函数 虚构
     */
    virtual ~GLSampleBase() {

    };

    virtual void loadImage(NativeImage *pImage) {
        LOGD("GLSampleBase::loadImage()");
    };

    virtual void loadMultiImageWithIndex(int index, NativeImage *pImage) {
        LOGD("GLSampleBase::loadMultiImageWithIndex() index=%d", index);
    };

    virtual void loadShortArrData(short *const pShortArr, int arrSize) {
        LOGD("GLSampleBase::loadShortArrData() pShortArr=%s, arrSize=%d", pShortArr, arrSize);
    };

    virtual void updateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY) {
        LOGD("GLSampleBase::updateTransformMatrix() rotateX=%f, rotateY=%f, scaleX=%f, scaleY=%f",
             rotateX, rotateY, scaleX, scaleY);
    };

    virtual void setTouchLocation(float x, float y) {
        LOGD("GLSampleBase::setTouchLocation() x=%f, y=%f", x, y);
    };

    virtual void setGravityXY(float x, float y) {
        LOGD("GLSampleBase::setGravityXY() x=%f, y=%f", x, y);
    };

    // 子类继承

    virtual void init() = 0;

    virtual void draw(int screenW, int screenH) = 0;

    virtual void destroy() = 0;

protected:
    GLuint m_vertexShader = 0;
    GLuint m_fragmentShader = 0;
    GLuint m_programObj = 0;
    int m_surfaceWidth = 0;
    int m_surfaceHeight = 0;
};

#endif //ANDROIDNATIVEOPENGLES_GLSAMPLEBASE_H

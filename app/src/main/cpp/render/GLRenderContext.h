//
// Created by windy on 2022/8/2.
//

#ifndef ANDROIDNATIVEOPENGLES_GLRENDERCONTEXT_H
#define ANDROIDNATIVEOPENGLES_GLRENDERCONTEXT_H


#include <GLSampleBase.h>
#include "CommonInclude.h"

class GLRenderContext {
public:
    static GLRenderContext *getInstance();

    static void destroyInstance();

    void onSurfaceCreated();

    void onSurfaceChanged(int width, int height);

    void onDrawFrame();

    void setImageData(int format, int width, int height, uint8_t *pData);

    void setImageDataWithIndex(int index, int format, int width, int height, uint8_t *pData);

    void updateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY);

    void setParamsFloat(int paramType, float value0, float value1);

    void setParamsInt(int paramType, int value0, int value1);

    void setParamsShortArr(short *const pShortArr, int arrSize);

private:
    GLRenderContext();

    ~GLRenderContext();

public:
    static GLRenderContext *instance;
    GLSampleBase *m_pBeforeSample{nullptr};
    GLSampleBase *m_pCurSample{nullptr};
    int m_screenW{0};
    int m_screenH{0};
};


#endif //ANDROIDNATIVEOPENGLES_GLRENDERCONTEXT_H

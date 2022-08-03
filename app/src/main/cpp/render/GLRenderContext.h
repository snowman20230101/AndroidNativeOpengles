//
// Created by windy on 2022/8/2.
//

#ifndef ANDROIDNATIVEOPENGLES_GLRENDERCONTEXT_H
#define ANDROIDNATIVEOPENGLES_GLRENDERCONTEXT_H


#include <GLSampleBase.h>
#include "CommonInclude.h"
#include "TriangleSample.h"

class GLRenderContext {
public:
    static GLRenderContext *getInstance();

    static void destroyInstance();

    void onSurfaceCreated();

    void onSurfaceChanged(int width, int height);

    void onDrawFrame();

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

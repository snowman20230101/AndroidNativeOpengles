//
// Created by windy on 2022/8/2.
//

#include "GLRenderContext.h"

GLRenderContext *GLRenderContext::instance = nullptr;

GLRenderContext::GLRenderContext() {
    LOGD("GLRenderContext::GLRenderContext()");
    m_pCurSample = new TriangleSample();
}

GLRenderContext::~GLRenderContext() {
    LOGD("GLRenderContext::~GLRenderContext()");
}

GLRenderContext *GLRenderContext::getInstance() {
    if (instance == nullptr) {
        instance = new GLRenderContext();
    }
    return instance;
}

void GLRenderContext::destroyInstance() {
    LOGD("GLRenderContext::destroyInstance()");
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

void GLRenderContext::onSurfaceCreated() {
    LOGD("GLRenderContext::onSurfaceCreated()");
//    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // call to OpenGL ES API with no current context (logged once per thread)
    // TODO 这里opengl 的 东西必须在 GLThread 中调用
    m_pCurSample->init();
}

void GLRenderContext::onSurfaceChanged(int width, int height) {
    LOGD("GLRenderContext::onSurfaceChanged() width=%d, height=%d", width, height);
    glViewport(0, 0, width, height);
    m_screenW = width;
    m_screenH = height;
}

void GLRenderContext::onDrawFrame() {
    LOGD("GLRenderContext::onDrawFrame()");
    if (m_pBeforeSample != nullptr) {
        m_pBeforeSample->destroy();
        delete m_pBeforeSample;
        m_pBeforeSample = nullptr;
    }

    if (m_pCurSample != nullptr) {
        m_pCurSample->draw(m_screenW, m_screenH);
    }
}

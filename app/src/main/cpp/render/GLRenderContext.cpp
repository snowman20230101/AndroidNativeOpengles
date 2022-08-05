//
// Created by windy on 2022/8/2.
//

#include "TriangleSample.h"
#include "BeatingHeartSample.h"
#include "GLRenderContext.h"
#include "CloudSample.h"

GLRenderContext *GLRenderContext::instance = nullptr;

GLRenderContext::GLRenderContext() {
    LOGD("GLRenderContext::GLRenderContext()");
//    m_pCurSample = new BeatingHeartSample();
    m_pCurSample = new TriangleSample();
//    m_pCurSample = new CloudSample();
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
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    if (m_pBeforeSample != nullptr) {
        m_pBeforeSample->destroy();
        delete m_pBeforeSample;
        m_pBeforeSample = nullptr;
    }

    if (m_pCurSample != nullptr) {
//        m_pCurSample->init();
        m_pCurSample->draw(m_screenW, m_screenH);
    }
}

void GLRenderContext::setImageData(int format, int width, int height, uint8_t *pData) {
    LOGD("GLRenderContext::setImageData format=%d, width=%d, height=%d, pData=%p", format,
         width, height, pData);

    NativeImage nativeImage;
    nativeImage.format = format;
    nativeImage.width = width;
    nativeImage.height = height;
    nativeImage.ppPlane[0] = pData;

    switch (format) {
        case IMAGE_FORMAT_NV12:
        case IMAGE_FORMAT_NV21:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            break;
        case IMAGE_FORMAT_I420:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            nativeImage.ppPlane[2] = nativeImage.ppPlane[1] + width * height / 4;
            break;
        default:
            break;
    }

    if (m_pCurSample) {
        m_pCurSample->loadImage(&nativeImage);
    }
}

void GLRenderContext::setImageDataWithIndex(int index, int format, int width, int height,
                                            uint8_t *pData) {
    LOGD("GLRenderContext::setImageDataWithIndex index=%d, format=%d, width=%d, height=%d, pData=%p",
         index, format, width, height, pData);
    NativeImage nativeImage;
    nativeImage.format = format;
    nativeImage.width = width;
    nativeImage.height = height;
    nativeImage.ppPlane[0] = pData;

    switch (format) {
        case IMAGE_FORMAT_NV12:
        case IMAGE_FORMAT_NV21:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            break;
        case IMAGE_FORMAT_I420:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            nativeImage.ppPlane[2] = nativeImage.ppPlane[1] + width * height / 4;
            break;
        default:
            break;
    }

    if (m_pCurSample) {
        m_pCurSample->loadMultiImageWithIndex(index, &nativeImage);
    }
}

void GLRenderContext::updateTransformMatrix(float rotateX, float rotateY,
                                            float scaleX, float scaleY) {
    LOGD("GLRenderContext::updateTransformMatrix [rotateX, rotateY, scaleX, scaleY] = [%f, %f, %f, %f]",
         rotateX, rotateY, scaleX, scaleY);

    if (m_pCurSample) {
        m_pCurSample->updateTransformMatrix(rotateX, rotateY, scaleX, scaleY);
    }
}

void GLRenderContext::setParamsFloat(int paramType, float value0, float value1) {
    LOGD("GLRenderContext::setParamsFloat paramType=%d, value0=%f, value1=%f", paramType,
         value0, value1);

    if (m_pCurSample) {
        switch (paramType) {
            case SAMPLE_TYPE_KEY_SET_TOUCH_LOC:
                m_pCurSample->setTouchLocation(value0, value1);
                break;
            case SAMPLE_TYPE_SET_GRAVITY_XY:
                m_pCurSample->setGravityXY(value0, value1);
                break;
            default:
                break;
        }
    }
}

void GLRenderContext::setParamsInt(int paramType, int value0, int value1) {
    LOGD("MyGLRenderContext::SetParamsInt paramType = %d, value0 = %d, value1 = %d", paramType,
         value0, value1);

    if (paramType == SAMPLE_TYPE) {
        m_pBeforeSample = m_pCurSample;

        LOGD("MyGLRenderContext::SetParamsInt 0 m_pBeforeSample = %p", m_pBeforeSample);

        switch (value0) {
            case SAMPLE_TYPE_KEY_TRIANGLE:
                m_pCurSample = new TriangleSample();
                break;
            default:
                m_pCurSample = nullptr;
                break;
        }

        LOGD("GLRenderContext::SetParamsInt m_pBeforeSample = %p, m_pCurSample=%p", m_pBeforeSample,
             m_pCurSample);
    }
}

void GLRenderContext::setParamsShortArr(short *const pShortArr, int arrSize) {
    LOGD("GLRenderContext::setParamsShortArr pShortArr=%p, arrSize=%d, pShortArr[0]=%d",
         pShortArr, arrSize, pShortArr[0]);
    if (m_pCurSample) {
        m_pCurSample->loadShortArrData(pShortArr, arrSize);
    }
}

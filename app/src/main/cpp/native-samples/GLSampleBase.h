//
// Created by windy on 2022/8/2.
//

#ifndef ANDROIDNATIVEOPENGLES_GLSAMPLEBASE_H
#define ANDROIDNATIVEOPENGLES_GLSAMPLEBASE_H

#include <ImageDef.h>
#include "CommonInclude.h"

#define SAMPLE_TYPE                             200
#define SAMPLE_TYPE_KEY_TRIANGLE                SAMPLE_TYPE + 0
#define SAMPLE_TYPE_KEY_TEXTURE_MAP             SAMPLE_TYPE + 1
#define SAMPLE_TYPE_KEY_YUV_TEXTURE_MAP         SAMPLE_TYPE + 2
#define SAMPLE_TYPE_KEY_VAO                     SAMPLE_TYPE + 3
#define SAMPLE_TYPE_KEY_FBO                     SAMPLE_TYPE + 4
#define SAMPLE_TYPE_KEY_FBO_LEG_LENGTHEN        SAMPLE_TYPE + 6
#define SAMPLE_TYPE_KEY_COORD_SYSTEM            SAMPLE_TYPE + 7
#define SAMPLE_TYPE_KEY_BASIC_LIGHTING          SAMPLE_TYPE + 8
#define SAMPLE_TYPE_KEY_TRANSFORM_FEEDBACK      SAMPLE_TYPE + 9
#define SAMPLE_TYPE_KEY_MULTI_LIGHTS            SAMPLE_TYPE + 10
#define SAMPLE_TYPE_KEY_DEPTH_TESTING           SAMPLE_TYPE + 11
#define SAMPLE_TYPE_KEY_INSTANCING              SAMPLE_TYPE + 12
#define SAMPLE_TYPE_KEY_STENCIL_TESTING         SAMPLE_TYPE + 13
#define SAMPLE_TYPE_KEY_BLENDING                SAMPLE_TYPE + 14
#define SAMPLE_TYPE_KEY_PARTICLES               SAMPLE_TYPE + 15
#define SAMPLE_TYPE_KEY_SKYBOX                  SAMPLE_TYPE + 16
#define SAMPLE_TYPE_KEY_3D_MODEL                SAMPLE_TYPE + 17
#define SAMPLE_TYPE_KEY_PBO                     SAMPLE_TYPE + 18
#define SAMPLE_TYPE_KEY_BEATING_HEART           SAMPLE_TYPE + 19
#define SAMPLE_TYPE_KEY_CLOUD                   SAMPLE_TYPE + 20
#define SAMPLE_TYPE_KEY_TIME_TUNNEL             SAMPLE_TYPE + 21
#define SAMPLE_TYPE_KEY_BEZIER_CURVE            SAMPLE_TYPE + 22
#define SAMPLE_TYPE_KEY_BIG_EYES                SAMPLE_TYPE + 23
#define SAMPLE_TYPE_KEY_FACE_SLENDER            SAMPLE_TYPE + 24
#define SAMPLE_TYPE_KEY_BIG_HEAD                SAMPLE_TYPE + 25
#define SAMPLE_TYPE_KEY_RATARY_HEAD             SAMPLE_TYPE + 26
#define SAMPLE_TYPE_KEY_VISUALIZE_AUDIO         SAMPLE_TYPE + 27
#define SAMPLE_TYPE_KEY_SCRATCH_CARD            SAMPLE_TYPE + 28
#define SAMPLE_TYPE_KEY_AVATAR                  SAMPLE_TYPE + 29
#define SAMPLE_TYPE_KEY_SHOCK_WAVE              SAMPLE_TYPE + 30
#define SAMPLE_TYPE_KEY_MRT                     SAMPLE_TYPE + 31
#define SAMPLE_TYPE_KEY_FBO_BLIT                SAMPLE_TYPE + 32
#define SAMPLE_TYPE_KEY_TBO                     SAMPLE_TYPE + 33
#define SAMPLE_TYPE_KEY_UBO                     SAMPLE_TYPE + 34
#define SAMPLE_TYPE_KEY_RGB2YUYV                SAMPLE_TYPE + 35
#define SAMPLE_TYPE_KEY_MULTI_THREAD_RENDER     SAMPLE_TYPE + 36
#define SAMPLE_TYPE_KEY_TEXT_RENDER            SAMPLE_TYPE + 37
#define SAMPLE_TYPE_KEY_STAY_COLOR            SAMPLE_TYPE + 38
#define SAMPLE_TYPE_KEY_TRANSITIONS_1            SAMPLE_TYPE + 39
#define SAMPLE_TYPE_KEY_TRANSITIONS_2            SAMPLE_TYPE + 40
#define SAMPLE_TYPE_KEY_TRANSITIONS_3            SAMPLE_TYPE + 41
#define SAMPLE_TYPE_KEY_TRANSITIONS_4            SAMPLE_TYPE + 42
#define SAMPLE_TYPE_KEY_RGB2NV21                SAMPLE_TYPE + 43
#define SAMPLE_TYPE_KEY_RGB2I420                SAMPLE_TYPE + 44
#define SAMPLE_TYPE_KEY_RGB2I444                SAMPLE_TYPE + 45
#define SAMPLE_TYPE_KEY_COPY_TEXTURE            SAMPLE_TYPE + 46
#define SAMPLE_TYPE_KEY_BLIT_FRAME_BUFFER       SAMPLE_TYPE + 47
#define SAMPLE_TYPE_KEY_BINARY_PROGRAM          SAMPLE_TYPE + 48
#define SAMPLE_TYPE_KEY_HWBuffer                SAMPLE_TYPE + 50

#define SAMPLE_TYPE_KEY_SET_TOUCH_LOC           SAMPLE_TYPE + 999
#define SAMPLE_TYPE_SET_GRAVITY_XY              SAMPLE_TYPE + 1000


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

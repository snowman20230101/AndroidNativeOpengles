//
// Created by windy on 2022/8/2.
//

#ifndef ANDROIDNATIVEOPENGLES_GLSAMPLEBASE_H
#define ANDROIDNATIVEOPENGLES_GLSAMPLEBASE_H

class GLSampleBase {
public:
    GLSampleBase();

    /**
     * 虚构函数虚构
     */
    virtual ~GLSampleBase();


    virtual void loadImage(NativeImage *pImage) {

    };

    virtual void loadMultiImageWithIndex(int index, NativeImage *pImage) {

    };

    virtual void loadShortArrData(short *const pShortArr, int arrSize) {

    }

    virtual void updateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY) {

    }

    virtual void setTouchLocation(float x, float y) {

    }

    virtual void setGravityXY(float x, float y) {

    }


    // 子类继承


    virtual void init() = 0;

    virtual void draw(int screenW, int screenH) = 0;

    virtual void destroy() = 0;

protected:
    GLuint m_vertexShader;
    GLuint m_fragmentShader;
    GLuint m_programObj;
    int m_surfaceWidth;
    int m_surfaceHeight;
};

GLSampleBase::GLSampleBase() {
    m_vertexShader = 0;
    m_fragmentShader = 0;
    m_programObj = -1;
    m_surfaceWidth = 0;
    m_surfaceHeight = 0;
}

GLSampleBase::~GLSampleBase() {

}

#endif //ANDROIDNATIVEOPENGLES_GLSAMPLEBASE_H

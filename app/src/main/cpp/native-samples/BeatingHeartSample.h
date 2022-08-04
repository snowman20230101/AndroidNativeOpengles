//
// Created by windy on 2022/8/4.
//

#ifndef ANDROIDNATIVEOPENGLES_BEATINGHEARTSAMPLE_H
#define ANDROIDNATIVEOPENGLES_BEATINGHEARTSAMPLE_H

#include "GLSampleBase.h"
#include "CommonInclude.h"
#include "ResourceManager.h"

/**
 * 心跳
 */
class BeatingHeartSample : public GLSampleBase {
public:
    BeatingHeartSample();

    ~BeatingHeartSample();

    virtual void init();

    virtual void draw(int screenW, int screenH);

    virtual void destroy();

    virtual void loadImage(NativeImage *pImage);

    virtual void updateTransformMatrix(float rotateX, float rotateY, float scaleX, float scaleY);

    void updateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY, float ratio);

private:
    GLuint m_textureId = GL_NONE;

    GLint m_MVPMatLoc = GL_NONE;

    GLint m_TimeLoc = GL_NONE;
    GLint m_SizeLoc = GL_NONE;

    GLuint m_VaoId = GL_NONE;
    GLuint m_VboIds[3]{};

    NativeImage m_RenderImage {};
    glm::mat4 m_MVPMatrix{};

    int m_AngleX = 0;
    int m_AngleY = 0;
    float m_ScaleX = 0;
    float m_ScaleY = 0;
};


#endif //ANDROIDNATIVEOPENGLES_BEATINGHEARTSAMPLE_H

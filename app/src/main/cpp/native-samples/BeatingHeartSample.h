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

    ~BeatingHeartSample() override;

    virtual void init() override;

    virtual void draw(int screenW, int screenH) override;

    virtual void destroy() override;

    virtual void loadImage(NativeImage *pImage) override;

    virtual void updateTransformMatrix(float rotateX, float rotateY,
                                       float scaleX, float scaleY) override;

private:
    virtual void updateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY, float ratio);

private:
    GLuint m_textureId = GL_NONE;
    GLint m_MVPMatLoc = GL_NONE;
    GLint m_TimeLoc = GL_NONE;
    GLint m_SizeLoc = GL_NONE;
    GLint m_SamplerLoc = GL_NONE;

    GLuint m_VaoId = GL_NONE;
    GLuint m_VboIds[3]{};

    NativeImage m_RenderImage{};
    glm::mat4 m_MVPMatrix{};

    int m_AngleX = 0;
    int m_AngleY = 0;
    float m_ScaleX = 0;
    float m_ScaleY = 0;

    GLfloat verticesCoords[12] = {
            -1.0f, 1.0f, 0.0f,  // Position 0
            -1.0f, -1.0f, 0.0f,  // Position 1
            1.0f, -1.0f, 0.0f,  // Position 2
            1.0f, 1.0f, 0.0f,  // Position 3
    };

    GLfloat textureCoords[8] = {
            0.0f, 0.0f,        // TexCoord 0
            0.0f, 1.0f,        // TexCoord 1
            1.0f, 1.0f,        // TexCoord 2
            1.0f, 0.0f         // TexCoord 3
    };

    GLushort indices[6] = {0, 1, 2, 0, 2, 3};
};


#endif //ANDROIDNATIVEOPENGLES_BEATINGHEARTSAMPLE_H

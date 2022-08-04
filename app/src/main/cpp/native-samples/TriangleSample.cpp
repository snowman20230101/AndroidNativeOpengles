//
// Created by windy on 2022/8/2.
//

#include <GLUtils.h>
#include "TriangleSample.h"
#include "ResourceManager.h"

TriangleSample::TriangleSample() {
    LOGD("TriangleSample::TriangleSample()");
}

TriangleSample::~TriangleSample() {
    LOGD("TriangleSample::~TriangleSample()");
}

void TriangleSample::loadImage(NativeImage *pImage) {
    LOGD("TriangleSample::loadImage()");
    // do Nothing
}

void TriangleSample::init() {
    LOGD("TriangleSample::init()");
    if (m_programObj != 0)
        return;

    char *vStr = ResourceManager::getInstance()->getShader2Triangle("triangle_vertex.glsl");
    char *fStr = ResourceManager::getInstance()->getShader2Triangle("triangle_fragment.glsl");
    LOGD("TriangleSample::init() \nvStr=%s\n, fStr=%s", vStr, fStr);

    m_programObj = GLUtils::createProgram(vStr, fStr, m_vertexShader, m_fragmentShader);

    free(vStr);
    free(fStr);
}

void TriangleSample::draw(int screenW, int screenH) {
    LOGD("TriangleSample::draw() screenW=%d, screenH=%d", screenW, screenH);
    GLfloat vVertices[] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };

    if (m_programObj == 0) {
        LOGI("TriangleSample::draw() m_programObj=%d", m_programObj);
        return;
    }

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Use the program object
    glUseProgram(m_programObj);

    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(GL_NONE);
}

void TriangleSample::destroy() {
    LOGD("TriangleSample::destroy() m_programObj=%d", m_programObj);
    if (m_programObj) {
        glDeleteProgram(m_programObj);
        m_programObj = GL_NONE;
    }
}

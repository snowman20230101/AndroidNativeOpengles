//
// Created by windy on 2022/8/2.
//

#include <GLUtils.h>
#include "TriangleSample.h"

TriangleSample::TriangleSample() = default;

TriangleSample::~TriangleSample() = default;

void TriangleSample::loadImage(NativeImage *pImage) {
    // do Nothing
}

void TriangleSample::init() {
    if (m_programObj != 0)
        return;
    char vShaderStr[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec4 vPosition;  \n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vPosition;              \n"
            "}                                        \n";

    char fShaderStr[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
            "}                                            \n";

    m_programObj = GLUtils::createProgram(vShaderStr, fShaderStr, m_vertexShader, m_fragmentShader);
}

void TriangleSample::draw(int screenW, int screenH) {
    GLfloat vVertices[] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };

    if (m_programObj == 0)
        return;

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Use the program object
    glUseProgram(m_programObj);

    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(GL_NONE);
}

void TriangleSample::destroy() {
    if (m_programObj) {
        glDeleteProgram(m_programObj);
        m_programObj = GL_NONE;
    }
}

//
// Created by windy on 2022/8/4.
//

#include "BeatingHeartSample.h"
#include "GLUtils.h"

BeatingHeartSample::BeatingHeartSample() {
    LOGD("BeatingHeartSample::BeatingHeartSample()");
}

BeatingHeartSample::~BeatingHeartSample() {
    LOGD("BeatingHeartSample::~BeatingHeartSample()");
}

void BeatingHeartSample::loadImage(NativeImage *pImage) {
    LOGD("BeatingHeartSample::loadImage() pImage = %p", pImage->ppPlane[0]);

    if (pImage != nullptr) {
        m_RenderImage.width = pImage->width;
        m_RenderImage.height = pImage->height;
        m_RenderImage.format = pImage->format;
        NativeImageUtil::CopyNativeImage(pImage, &m_RenderImage);
    }
}

void BeatingHeartSample::init() {
    LOGD("BeatingHeartSample::init()");
    if (m_programObj != 0)
        return;

    // create RGBA texture
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    const char *vStr = ResourceManager::getInstance()->getShaderSource("beatingheart_vertex.glsl");
    const char *fStr = ResourceManager::getInstance()->getShaderSource(
            "beatingheart_fragment.glsl");
    m_programObj = GLUtils::createProgram(vStr, fStr, m_vertexShader, m_fragmentShader);

    if (m_programObj) {
        // m_SamplerLoc = glGetUniformLocation(m_ProgramObj, "s_TextureMap");
        m_MVPMatLoc = glGetUniformLocation(m_programObj, "u_MVPMatrix");
        m_SizeLoc = glGetUniformLocation(m_programObj, "u_screenSize");
        m_TimeLoc = glGetUniformLocation(m_programObj, "u_time");
    } else {
        LOGE("BeatingHeartSample::init() create program failed. ");
    }

    // Generate VBO Ids and load the VBOs with data
    glGenBuffers(3, m_VboIds);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCoords), verticesCoords, GL_STATIC_DRAW);

//    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[1]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VboIds[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Generate VAO Id
    glGenVertexArrays(1, &m_VaoId);
    glBindVertexArray(m_VaoId);

    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

//	glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[1]);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (const void *)0);
//	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VboIds[2]);

    glBindVertexArray(GL_NONE);
}

void BeatingHeartSample::draw(int screenW, int screenH) {
    LOGD("BeatingHeartSample::Draw() screenW=%d, screenH=%d", screenW, screenH);

    updateMVPMatrix(m_MVPMatrix, m_AngleX, m_AngleY, (float) screenW / screenH);

    // upload RGBA image data
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, m_TextureId);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_RenderImage.width, m_RenderImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_RenderImage.ppPlane[0]);
//	glBindTexture(GL_TEXTURE_2D, GL_NONE);

    // Use the program object
    glUseProgram(m_programObj);

    glBindVertexArray(m_VaoId);

    glUniformMatrix4fv(m_MVPMatLoc, 1, GL_FALSE, &m_MVPMatrix[0][0]);
    float time = static_cast<float>(fmod(GetSysCurrentTime(), 2000) / 2000);

    LOGD("BeatingHeartSample::Draw() time=%f", time);

    glUniform1f(m_TimeLoc, time);
    glUniform2f(m_SizeLoc, screenW, screenH);

//	// Bind the RGBA map
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, m_TextureId);
//	glUniform1i(m_SamplerLoc, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const void *) 0);
}

void BeatingHeartSample::destroy() {
    LOGD("BeatingHeartSample::destroy() m_programObj=%d", m_programObj);

    if (m_programObj) {
        glDeleteProgram(m_programObj);
        m_programObj = GL_NONE;
        glDeleteBuffers(3, m_VboIds);
        glDeleteVertexArrays(1, &m_VaoId);
        glDeleteTextures(1, &m_textureId);
    }
}

void BeatingHeartSample::updateTransformMatrix(float rotateX, float rotateY, float scaleX,
                                               float scaleY) {
    GLSampleBase::updateTransformMatrix(rotateX, rotateY, scaleX, scaleY);
    m_AngleX = static_cast<int>(rotateX);
    m_AngleY = static_cast<int>(rotateY);
    m_ScaleX = scaleX;
    m_ScaleY = scaleY;
}

void BeatingHeartSample::updateMVPMatrix(glm::mat4 &mvpMatrix, int angleX,
                                         int angleY, float ratio) {
    LOGD("BeatingHeartSample::updateMVPMatrix angleX = %d, angleY = %d, ratio = %f", angleX, angleY,
         ratio);

    angleX = angleX % 360;
    angleY = angleY % 360;

    //转化为弧度角
    float radiansX = static_cast<float>(MATH_PI / 180.0f * angleX);
    float radiansY = static_cast<float>(MATH_PI / 180.0f * angleY);

    // Projection matrix
    glm::mat4 Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    // glm::mat4 Projection = glm::frustum(-ratio, ratio, -1.0f, 1.0f, 4.0f, 100.0f);
    // glm::mat4 Projection = glm::perspective(45.0f,ratio, 0.1f,100.f);

    // View matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(0, 0, 4), // Camera is at (0,0,1), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix
    glm::mat4 Model = glm::mat4(1.0f);
    Model = glm::scale(Model, glm::vec3(m_ScaleX, m_ScaleY, 1.0f));
    Model = glm::rotate(Model, radiansX, glm::vec3(1.0f, 0.0f, 0.0f));
    Model = glm::rotate(Model, radiansY, glm::vec3(0.0f, 1.0f, 0.0f));
    Model = glm::translate(Model, glm::vec3(0.0f, 0.0f, 0.0f));

    mvpMatrix = Projection * View * Model;
}

//
// Created by windy on 2022/8/2.
//

#include "GLUtils.h"

GLuint GLUtils::loadShader(GLenum shaderType, const char *pSource) {
    GLuint shaderId;
    FUN_BEGIN_TIME("GLUtils::loadShader")
        shaderId = glCreateShader(shaderType);
        glShaderSource(shaderId, 1, &pSource, NULL);
        glCompileShader(shaderId);
        GLint compiled = 0;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char *buf = (char *) malloc((size_t) infoLen);
                if (buf) {
                    glGetShaderInfoLog(shaderId, infoLen, NULL, buf);
                    LOGE("GLUtils::loadShader Could not compile shader %d:\n%s\n",
                         shaderType,
                         buf);
                    free(buf);
                }
                glDeleteShader(shaderId);
                shaderId = 0;
            }
        }
    FUN_END_TIME("GLUtils::loadShader")

    LOGD("GLUtils::loadShader() shaderId=%d", shaderId);
    return shaderId;
}

GLuint GLUtils::createProgram(const char *pVertexShaderSource, const char *pFragShaderSource,
                              GLuint &vertexShaderHandle, GLuint &fragShaderHandle) {
    GLuint program = 0;
    FUN_BEGIN_TIME("GLUtils::createProgram")
        vertexShaderHandle = loadShader(GL_VERTEX_SHADER, pVertexShaderSource);
        if (!vertexShaderHandle) return program;
        fragShaderHandle = loadShader(GL_FRAGMENT_SHADER, pFragShaderSource);
        if (!fragShaderHandle) return program;

        program = glCreateProgram();
        if (program) {
            glAttachShader(program, vertexShaderHandle);
            checkGlError("glAttachShader");
            glAttachShader(program, fragShaderHandle);
            checkGlError("glAttachShader");
            glLinkProgram(program);
            GLint linkStatus = GL_FALSE;
            glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

            glDetachShader(program, vertexShaderHandle);
            glDeleteShader(vertexShaderHandle);
            vertexShaderHandle = 0;
            glDetachShader(program, fragShaderHandle);
            glDeleteShader(fragShaderHandle);
            fragShaderHandle = 0;
            if (linkStatus != GL_TRUE) {
                GLint bufLength = 0;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
                if (bufLength) {
                    char *buf = (char *) malloc((size_t) bufLength);
                    if (buf) {
                        glGetProgramInfoLog(program, bufLength, NULL, buf);
                        LOGE("GLUtils::createProgram Could not link program:\n%s\n", buf);
                        free(buf);
                    }
                }
                glDeleteProgram(program);
                program = 0;
            }
        }
    FUN_END_TIME("GLUtils::createProgram")
    LOGD("GLUtils::createProgram program = %d", program);
    return program;
}

GLuint GLUtils::createProgram(const char *pVertexShaderSource, const char *pFragShaderSource) {
    GLuint vertexShaderHandle, fragShaderHandle;
    return createProgram(pVertexShaderSource, pFragShaderSource, vertexShaderHandle,
                         fragShaderHandle);
}

GLuint GLUtils::createProgramWithFeedback(const char *pVertexShaderSource,
                                          const char *pFragShaderSource,
                                          GLuint &vertexShaderHandle, GLuint &fragShaderHandle,
                                          GLchar const **varying, int varyingCount) {
    GLuint program = 0;
    FUN_BEGIN_TIME("GLUtils::createProgramWithFeedback")
        vertexShaderHandle = loadShader(GL_VERTEX_SHADER, pVertexShaderSource);
        if (!vertexShaderHandle) return program;

        fragShaderHandle = loadShader(GL_FRAGMENT_SHADER, pFragShaderSource);
        if (!fragShaderHandle) return program;

        program = glCreateProgram();
        if (program) {
            glAttachShader(program, vertexShaderHandle);
            checkGlError("glAttachShader");
            glAttachShader(program, fragShaderHandle);
            checkGlError("glAttachShader");

            //transform feedback
            glTransformFeedbackVaryings(program, varyingCount, varying, GL_INTERLEAVED_ATTRIBS);
            GO_CHECK_GL_ERROR();

            glLinkProgram(program);
            GLint linkStatus = GL_FALSE;
            glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

            glDetachShader(program, vertexShaderHandle);
            glDeleteShader(vertexShaderHandle);
            vertexShaderHandle = 0;
            glDetachShader(program, fragShaderHandle);
            glDeleteShader(fragShaderHandle);
            fragShaderHandle = 0;
            if (linkStatus != GL_TRUE) {
                GLint bufLength = 0;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
                if (bufLength) {
                    char *buf = (char *) malloc((size_t) bufLength);
                    if (buf) {
                        glGetProgramInfoLog(program, bufLength, NULL, buf);
                        LOGE("GLUtils::createProgramWithFeedback Could not link program:\n%s\n",
                             buf);
                        free(buf);
                    }
                }
                glDeleteProgram(program);
                program = 0;
            }
        }
    FUN_END_TIME("GLUtils::createProgramWithFeedback")
    LOGE("GLUtils::createProgramWithFeedback program = %d", program);
    return program;
}

void GLUtils::deleteProgram(GLuint &program) {
    LOGE("GLUtils::deleteProgram");
    if (program) {
        glUseProgram(0);
        glDeleteProgram(program);
        program = 0;
    }
}

void GLUtils::checkGlError(const char *pGLOperation) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGE("GLUtils::checkGlError GL Operation %s() glError (0x%x)\n", pGLOperation, error);
    }

}
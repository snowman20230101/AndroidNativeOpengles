//
// Created by windy on 2022/8/2.
//

#ifndef ANDROIDNATIVEOPENGLES_GLUTILS_H
#define ANDROIDNATIVEOPENGLES_GLUTILS_H

#include <GLES3/gl3.h>
#include <string>
#include <glm.hpp>
#include "CommonInclude.h"

#define MATH_PI 3.1415926535897932384626433832802

class GLUtils {
public:
    /**
     * 加载 着色器
     *
     * @param shaderType
     * @param pSource
     * @return
     */
    static GLuint loadShader(GLenum shaderType, const char *pSource);

    /**
     * 创建程序
     *
     * @param pVertexShaderSource
     * @param pFragShaderSource
     * @param vertexShaderHandle
     * @param fragShaderHandle
     * @return
     */
    static GLuint createProgram(const char *pVertexShaderSource, const char *pFragShaderSource,
                                GLuint &vertexShaderHandle,
                                GLuint &fragShaderHandle);

    /**
     * 创建程序
     *
     * @param pVertexShaderSource
     * @param pFragShaderSource
     * @return
     */
    static GLuint createProgram(const char *pVertexShaderSource, const char *pFragShaderSource);

    static GLuint createProgramWithFeedback(
            const char *pVertexShaderSource,
            const char *pFragShaderSource,
            GLuint &vertexShaderHandle,
            GLuint &fragShaderHandle,
            const GLchar **varying,
            int varyingCount);

    static void deleteProgram(GLuint &program);

    static void checkGlError(const char *pGLOperation);

    static void setBool(GLuint programId, const std::string &name, bool value) {
        glUniform1i(glGetUniformLocation(programId, name.c_str()), (int) value);
    }

    static void setInt(GLuint programId, const std::string &name, int value) {
        glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
    }

    static void setFloat(GLuint programId, const std::string &name, float value) {
        glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
    }

    static void setVec2(GLuint programId, const std::string &name, const glm::vec2 &value) {
        glUniform2fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
    }

    static void setVec2(GLuint programId, const std::string &name, float x, float y) {
        glUniform2f(glGetUniformLocation(programId, name.c_str()), x, y);
    }

    static void setVec3(GLuint programId, const std::string &name, const glm::vec3 &value) {
        glUniform3fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
    }

    static void setVec3(GLuint programId, const std::string &name, float x, float y, float z) {
        glUniform3f(glGetUniformLocation(programId, name.c_str()), x, y, z);
    }

    static void setVec4(GLuint programId, const std::string &name, const glm::vec4 &value) {
        glUniform4fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
    }

    static void
    setVec4(GLuint programId, const std::string &name, float x, float y, float z, float w) {
        glUniform4f(glGetUniformLocation(programId, name.c_str()), x, y, z, w);
    }

    static void setMat2(GLuint programId, const std::string &name, const glm::mat2 &mat) {
        glUniformMatrix2fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    static void setMat3(GLuint programId, const std::string &name, const glm::mat3 &mat) {
        glUniformMatrix3fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    static void setMat4(GLuint programId, const std::string &name, const glm::mat4 &mat) {
        glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    static glm::vec3 texCoordToVertexCoord(glm::vec2 &texCoord) {
        return glm::vec3(2 * texCoord.x - 1, 1 - 2 * texCoord.y, 0);
    }

};


#endif //ANDROIDNATIVEOPENGLES_GLUTILS_H

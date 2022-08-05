//
// Created by windy on 2022/8/5.
//

#include "GLUtils.h"
#include "CloudSample.h"

CloudSample::CloudSample() {
    LOGD("CloudSample::CloudSample()");
}

CloudSample::~CloudSample() {
    LOGD("CloudSample::~CloudSample()");
}

void CloudSample::init() {
    if (m_programObj != 0)
        return;
    auto vStr = ResourceManager::getInstance()->getShaderSource("beatingheart_vertex.glsl");
    auto fStr = ResourceManager::getInstance()->getShaderSource("beatingheart_fragment.glsl");
    m_programObj = GLUtils::createProgram(vStr, fStr, m_vertexShader, m_fragmentShader);
}

void CloudSample::draw(int screenW, int screenH) {

}

void CloudSample::destroy() {

}

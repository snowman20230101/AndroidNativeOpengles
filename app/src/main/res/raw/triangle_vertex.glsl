#version 300 es
layout(location = 0) in vec4 vPostion;

void main() {
    gl_Position = vPostion;
}
#version 440 core

layout (location = 0) in vec3 position;

uniform mat4 pos;
uniform mat4 projView;

void main() {
    gl_Position = projView * pos * vec4(position.xyz, 1.0);
}
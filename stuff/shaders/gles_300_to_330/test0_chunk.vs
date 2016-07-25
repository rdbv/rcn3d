#version 330
layout (location = 0) in vec4 pos;

uniform mat4 mvp;

out vec4 texcoord;

void main() {
    texcoord = pos;
    gl_Position = mvp * vec4(pos.xyz, 1.0);
}


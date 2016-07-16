#version 300 es
layout (location = 0) in vec4 pos;

uniform mat4 mvp;

flat out ivec4 pos_i;

void main() {
    pos_i = ivec4(pos);
    gl_Position = mvp * vec4(pos.xyz, 1.0);
}


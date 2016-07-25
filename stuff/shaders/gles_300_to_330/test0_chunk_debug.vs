#version 330
layout (location = 0) in vec4 pos;

uniform mat4 mvp;

out vec4 pos_i;

void main() {
    pos_i = vec4(pos);
    gl_Position = mvp * vec4(pos.xyz, 1.0);
}


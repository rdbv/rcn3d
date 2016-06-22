#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

out vec3 out_col;

uniform mat4 mvp;

void main() {
    out_col = col;
    gl_Position = mvp * vec4(pos.x, pos.y, pos.z, 1.0);
}

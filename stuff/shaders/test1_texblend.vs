#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

out vec2 uv_data;

uniform mat4 mvp;

void main() {
    uv_data = uv;
    gl_Position = mvp * vec4(pos.x, pos.y, pos.z, 1.0);
}

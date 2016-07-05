#version 300 es
layout (location = 0) in mediump vec3 pos;
layout (location = 1) in mediump vec2 uv;

out mediump vec2 uv_data;
uniform mat4 mvp;

void main() {
    uv_data = uv;
    gl_Position = mvp * vec4(pos, 1.0);
}


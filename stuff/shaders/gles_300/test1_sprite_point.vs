#version 300 es

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
out mediump vec3 out_col;
uniform mat4 mvp;
void main() {
    out_col = col;
    gl_Position = mvp * vec4(pos, 1.0);
    gl_PointSize = max(1.0, 8.0f);
}

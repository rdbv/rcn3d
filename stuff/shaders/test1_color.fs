#version 330 core
in vec3 out_col;
out vec4 color;
void main() {
    color = vec4(out_col, 1.0f);
}

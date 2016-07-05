#version 300 es
in mediump vec3 out_col;
out mediump vec4 color;
void main() {
    color = vec4(out_col, 1.0);
}


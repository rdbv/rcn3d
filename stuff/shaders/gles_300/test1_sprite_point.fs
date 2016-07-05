#version 300 es
in mediump vec3 out_col;
out mediump vec4 color;
uniform sampler2D point_tex;

void main() {
    color = texture2D(point_tex, gl_PointCoord) * vec4(out_col, 1.0);
}

#version 300 es
in mediump vec2 uv_data;
out mediump vec4 color;

uniform sampler2D tex0;

void main() {
    mediump vec4 pixel_color = texture(tex0, uv_data);
    if(pixel_color.a < 0.1)
        discard;
    color = pixel_color;
}


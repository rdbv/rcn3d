#version 330 core

in vec2 uv_data;
out vec4 color;

uniform sampler2D tex0;

void main() {
    vec4 pixel_color = texture(tex0, uv_data);
    if(pixel_color.a < 0.1)
        discard;
    color = pixel_color;    
    
}

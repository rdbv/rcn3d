#version 330 core

in vec2 uv_data;
out vec4 color;

uniform sampler2D tex0;

void main() {
    color = texture(tex0, uv_data);    
}

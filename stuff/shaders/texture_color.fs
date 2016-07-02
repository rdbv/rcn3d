#version 330 core

in vec2 uv_data;
out vec4 color;

uniform sampler2D tex0;
uniform float r;
uniform float g;
uniform float b;
uniform float a;

void main() {
    color = texture(tex0, uv_data) * vec4(r, g, b, a);    
}

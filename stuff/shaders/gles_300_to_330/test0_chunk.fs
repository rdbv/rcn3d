#version 330

in  vec4 texcoord;
out vec4 color;

uniform sampler2D tex_mc;

void main() {
    mediump vec2 coord2d;
    if(texcoord.w < 0.0)
        coord2d = vec2((fract(texcoord.x) + texcoord.w) / 16.0, texcoord.z);
    else
        coord2d = vec2((fract(texcoord.x + texcoord.z) + texcoord.w) / 16.0, -texcoord.y);

    color = texture2D(tex_mc, coord2d);
}


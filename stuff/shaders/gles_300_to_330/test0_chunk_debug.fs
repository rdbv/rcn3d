#version 330

in  vec4 pos_i;
out vec4 color;

void main() {
    if(pos_i.w == 0)
        color = vec4(0, 1.0, 0, 0);
    if(pos_i.w == 1)
        color = vec4(0, 0, 1.0, 0);
    if(pos_i.w == 2)
        color = vec4(1, 0, 0, 0);
    if(pos_i.w == 3)
        color = vec4(0.5, 0.5, 0, 0);
    if(pos_i.w == 4)
        color = vec4(0.25, 0.5, 0, 0);
    if(pos_i.w == 5)
        color = vec4(0.50, 0.0, 0.25, 0);
}


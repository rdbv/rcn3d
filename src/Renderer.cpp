#include "../include/Renderer.hpp"

using namespace rcn3d;

void Renderer::clearScreen(glm::vec4 color) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, color.a);    
}

void Renderer::setWireframeMode(bool en) {
    if(en)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::setLineWidth(float w) {
    glLineWidth(w);
}




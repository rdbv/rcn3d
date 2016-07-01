#include "../include/Renderer.hpp"

using namespace rcn3d;

void Renderer::enableWireframe(bool en) {
    if(en)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



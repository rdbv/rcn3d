#include "../include/Renderer.hpp"

using namespace rcn3d;

Env Renderer::env;
std::map<std::string, Renderable*> Renderer::objects;

void Renderer::clearScreen(glm::vec4 color) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, color.a);    
}

void Renderer::setProjMatrix(glm::mat4 mproj) {
    env.mx_proj = mproj;
}

void Renderer::setViewMatrix(glm::mat4 mview) {
    env.mx_view = mview;
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


void Renderer::renderAll() {
    glm::mat4 mvp;
    for(const auto& p : objects) {
        auto obj = p.second;
        obj->getShader()->run();

        obj->getVertexArray()->bind(0);
        mvp = env.mx_proj * env.mx_view * obj->getGlobalTransformMatrix();
        obj->getShader()->setUniform("mvp", mvp);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        obj->getVertexArray()->unbind();
    }
}

Renderable* Renderer::createRenderable(std::string n) {
    if(objects.count(n))
        return nullptr;
    objects[n] = new Renderable();
    return objects[n];
}


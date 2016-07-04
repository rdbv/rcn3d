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

/* Jest glDrawArrays ale prawdopodobnie będą używane bufory indeksowe(glDrawElements), 
 * więc to jest do przeróbki
 */

void Renderer::renderAll() {
    glm::mat4 mvp;
    for(const auto& p : objects) {
        auto obj = p.second;
        auto vao = obj->getVertexArray();
        auto shr = obj->getShader();

        shr->run();

        vao->bind(0);

        mvp = env.mx_proj * env.mx_view * obj->getGlobalTransformMatrix();

        shr->setUniform("mvp", mvp);
        
        glDrawArrays(vao->getDrawType(), 0, vao->getVertexCount());

        vao->unbind();
    }
}

Renderable* Renderer::createRenderable(std::string n) {
    if(objects.count(n)) {
#ifdef _RENDERER_DUMP_ERRORS
        printf("[%s] Object %s already exist in map!\n", __FUNCTION__, n.c_str());
#endif
        return nullptr;
    }
    objects[n] = new Renderable();
    return objects[n];
}

Renderable* Renderer::getRenderable(std::string n) {
    if(objects.count(n) == 0)
        return nullptr;
    else 
        return objects[n];
}

void Renderer::destroyAllRenderables() {
    for(const auto& p : objects) {
        auto obj = p.second;
        obj->getVertexArray()->deleteVertexArrays();
        delete obj;
    }
}

bool Renderer::destroyRenderable(std::string n) {
    if(objects.count(n) == 0) {
#ifdef _RENDERER_DUMP_ERRORS
        printf("[%s] Object %s doesn't exists in map!\n", __FUNCTION__, n.c_str());
#endif
        return false;
    }
    else { 
        auto obj = objects[n];
        obj->getVertexArray()->deleteVertexArrays();

        delete objects[n];
    }
    return true;
}


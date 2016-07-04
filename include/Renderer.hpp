#ifndef RENDERER_HPP
#define RENDERER_HPP

#define GLEW_STATIC 
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "header_only/Renderable.hpp"
#include "header_only/VertexArray.hpp"

namespace rcn3d {

struct Env
{
    glm::mat4 mx_proj;
    glm::mat4 mx_view;
};

/* Pipeline wrapper */

class Renderer 
{
public:

    static Renderer& getInstance() {
        static Renderer r;
        return r;
    }

    /* Functions changing GL state */
    void clearScreen(glm::vec4);

    void setProjMatrix(glm::mat4);
    void setViewMatrix(glm::mat4);

    void setWireframeMode(bool);
    void setLineWidth(float);

    Renderable* createRenderable(std::string);

    void renderAll();
    /* Simple render functions */
    //void renderVertexArray(GLenum

private:

    static Env env;
    static std::map<std::string, Renderable*> objects;

    Renderer() {}
    Renderer(const Renderer&)   = delete;
    void operator=(Renderer&)   = delete;
};

} // namespace rcn3d

#endif

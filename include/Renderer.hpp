#ifndef RENDERER_HPP
#define RENDERER_HPP

#define GLEW_STATIC 
#include <GL/glew.h>
#include <glm/glm.hpp>

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

    void setWireframeMode(bool);
    void setLineWidth(float);

    /* Simple render functions */
    //void renderVertexArray(GLenum

private:

    Env env;

    Renderer() {}
    Renderer(const Renderer&)   = delete;
    void operator=(Renderer&)   = delete;
};

} // namespace rcn3d

#endif

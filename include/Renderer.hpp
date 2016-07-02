#ifndef RENDERER_HPP
#define RENDERER_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include "header_only/VertexArray.hpp"
#include "header_only/Math.hpp"
#include "ShaderProgram.hpp"

namespace rcn3d {

/* Pipeline wrapper */

class Renderer
{
public:

    static Renderer& getInstance() {
        static Renderer r;
        return r;
    }

    void enableWireframe(bool);

    static VertexArray spriteVAO;
    static ShaderProgram spriteShader;
    static void getSpriteVAO();
    static void initRenderer() {
        getSpriteVAO();
        spriteShader.load("stuff/shaders/texture_color.vs",
                    "stuff/shaders/texture_color.fs");
        spriteShader.addUniforms({"mvp","tex0","r","g","b","a"});
    }

private:
    Renderer() {}
    Renderer(const Renderer&)   = delete;
    void operator=(Renderer&)   = delete;
};

} // namespace rcn3d

#endif

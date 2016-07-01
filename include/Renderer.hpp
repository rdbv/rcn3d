#ifndef RENDERER_HPP
#define RENDERER_HPP

#define GLEW_STATIC 
#include <GL/glew.h>

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

private:
    Renderer() {}
    Renderer(const Renderer&)   = delete;
    void operator=(Renderer&)   = delete;
};

} // namespace rcn3d

#endif

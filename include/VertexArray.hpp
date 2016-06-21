#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#define GLEW_STATIC 
#include <GL/glew.h>

namespace rcn3d {

class VertexArray 
{
public:
    VertexArray() {
    }

    void bind();
    void unbind();
    GLuint getID();

    void createVertexArray();
    void deleteVertexArray();

private:

    GLuint obj = 0;
};

} // namespace rcn3d

#endif

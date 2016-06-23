#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#define GLEW_STATIC 
#include <GL/glew.h>
#include <vector>
#include <cassert>

namespace rcn3d {

class VertexArray 
{
public:
   
    VertexArray() {
        vx.resize(size);
    }

    VertexArray(std::size_t n) 
        : size(n) {
        assert(n > 0);    
        vx.resize(n);
    }

    void bind(std::size_t n = 0);
    void unbind();


    void createVertexArrays();
    void deleteVertexArrays();

private:

    std::vector<GLuint> vx;
    std::size_t size = 1;
};

} // namespace rcn3d

#endif

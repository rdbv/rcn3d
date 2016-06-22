#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#define GLEW_STATIC 
#include <GL/glew.h>
#include <vector>
#include <cstdint>
#include <cassert>

namespace rcn3d {

class VertexBuffer
{   
public:
    VertexBuffer(std::size_t n)
        : size(n) {
            buf.resize(size);
    }

    inline void createVertexBuffers() {
        glGenBuffers(size, &buf[0]);
    }

    inline void deleteBuffers() {
        glDeleteBuffers(size, &buf[0]);
    }

    inline void bind(GLenum t, std::size_t n) {
        assert(n < size);
        glBindBuffer(t, buf[n]); 
    }


private:

    std::vector<GLuint> buf;
    std::size_t size = 0;
};

} // namespace rcn3d

#endif

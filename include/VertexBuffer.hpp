#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#define GLEW_STATIC 
#include <GL/glew.h>
#include <vector>
#include <cstdio>
#include <cstdint>
#include <cassert>

#define VBO_DEBUG_PRINTF

namespace rcn3d {

class VertexBuffer
{   
public:
    VertexBuffer(std::size_t n)
        : size(n) {
            buf.resize(size);
    }

    inline void createVertexBuffers() {
#ifdef VBO_DEBUG_PRINTF
        printf("[%s] size:%lu\n", __FUNCTION__, size);
#endif
        glGenBuffers(size, &buf[0]);
    }

    inline void deleteVertexBuffers() {
#ifdef VBO_DEBUG_PRINTF
        printf("[%s] size:%lu\n", __FUNCTION__, size);
#endif
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

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
    inline void createVertexBuffers(std::size_t n) {
#ifdef VBO_DEBUG_PRINTF
        printf("[%s] size:%lu (%lu)\n", __FUNCTION__, size, n);
#endif
        size = n;
        buf.resize(n);
        glGenBuffers(size, &buf[0]);
    }

    inline void deleteVertexBuffers() {
#ifdef VBO_DEBUG_PRINTF
        printf("[%s] size:%lu\n", __FUNCTION__, size);
#endif
        assert(size != 0);
        glDeleteBuffers(size, &buf[0]);
    }

    inline void bind(GLenum t, std::size_t n) {
        type = t;
        assert(n < size);
        glBindBuffer(t, buf[n]); 
    }

    inline GLenum getType() {
        return type;
    }

private:

    GLenum type;
    std::vector<GLuint> buf;
    std::size_t size = 1;
};

} // namespace rcn3d

#endif

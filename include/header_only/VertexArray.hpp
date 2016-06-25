#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#define GLEW_STATIC 
#define VAO_DEBUG_PRINTF

#include <GL/glew.h>
#include <map>
#include <cstdio>
#include <vector>
#include <cassert>
#include <memory>

namespace rcn3d {

class VertexArray 
{
public:

    inline void bind(std::size_t n) {
        assert(n < size);
        glBindVertexArray(vx[n]);
    }

    inline void unbind() {
        glBindVertexArray(0);
    }

    inline void createVertexArrays(std::size_t n) {
#ifdef VAO_DEBUG_PRINTF
        printf("[%s] size:%lu\n", __FUNCTION__, size);
#endif
        assert(n != 0);
        size = n;
        vx.resize(n);
        glGenVertexArrays(size, &vx[0]); 
    }

    inline void deleteVertexArrays() {
#ifdef VAO_DEBUG_PRINTF
        printf("[%s] size:%lu\n", __FUNCTION__, size);
#endif
        glDeleteVertexArrays(size, &vx[0]);
    }

private:

    std::vector<GLuint> vx;
    std::size_t size = 1;
};

} // namespace rcn3d

#endif

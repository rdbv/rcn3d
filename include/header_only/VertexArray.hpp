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
#include "VertexBuffer.hpp"

namespace rcn3d {

class VertexArray 
{
public:
    inline void createVertexArrays(std::size_t n) {
#ifdef VAO_DEBUG_PRINTF
        printf("[%s] size:%lu\n", __FUNCTION__, size);
#endif
        assert(n != 0);
        size = n;
        vx.resize(n);
        vb_data.resize(n);
        glGenVertexArrays(size, &vx[0]); 
    }

    inline void deleteVertexArrays() {
#ifdef VAO_DEBUG_PRINTF
        printf("[%s] size:%lu\n", __FUNCTION__, size);
#endif
        glDeleteVertexArrays(size, &vx[0]);
        for(auto &buf : vb_data)
            buf.deleteVertexBuffers();
    }

    void addVertexBuffer(std::size_t vao_id, VertexBuffer buf) {
        assert(vao_id < size);
        vb_data[vao_id] = buf;
    }

    inline void bind(std::size_t n) {
        assert(n < size);
        glBindVertexArray(vx[n]);
    }

    inline void unbind() {
        glBindVertexArray(0);
    }

    std::size_t poly_count = 0;
    GLenum poly_type = GL_TRIANGLES;

private:
    std::vector<VertexBuffer> vb_data;
    std::vector<GLuint> vx;
    std::size_t size = 1;
};

} // namespace rcn3d

#endif

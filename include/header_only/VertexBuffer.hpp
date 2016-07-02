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

struct BufferData
{
    GLenum bind_target;
    std::size_t n = 0;
    std::size_t size = 0;
    unsigned int dataCount = 0;

};

class VertexBuffer
{   
public:
    inline void createVertexBuffers(std::size_t n) {
#ifdef VBO_DEBUG_PRINTF
        printf("[%s] size:%lu (%lu)\n", __FUNCTION__, size, n);
#endif
        size = n;
        buf.resize(n);
        buf_data.resize(n);
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
        assert(n < size);
        binded = n;
        buf_data[n].bind_target = t;
        glBindBuffer(t, buf[n]); 
    }

    inline BufferData getBufferData(std::size_t n) const {
        assert(n < size);
        return buf_data[n];
    }

    /* OpenGL Calls wrapper */

    inline void bufferData_gl (const GLvoid* data, std::size_t dataSize, GLenum usage = GL_STATIC_DRAW) {
        auto d = buf_data[binded];
        buf_data[binded].size = dataSize;
        glBufferData(d.bind_target, dataSize, data, usage);  
    }

    inline void vxAttribPtr_gl(std::size_t n, unsigned int dc, GLenum type,
                               GLenum normalized, std::size_t stride, const GLvoid* ptr) {
        buf_data[binded].n = n;
        buf_data[binded].dataCount = dc;
        glVertexAttribPointer(n, dc, type, normalized, stride, ptr);
    }


private:

    std::vector<GLuint> buf;
    std::vector<BufferData> buf_data;

    std::size_t size = 1;
    std::size_t binded = 0;

};

} // namespace rcn3d

#endif

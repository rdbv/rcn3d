#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#define GLEW_STATIC 
#include <GL/glew.h>
#include <map>
#include <vector>
#include <cstdio>
#include <cstdint>
#include <cassert>

#define VBO_DEBUG_PRINTF

template<typename T> std::size_t siz(const std::vector<T>& t) { return t.size() * sizeof(T); }

static std::map<GLenum, const char*> targets {
    {GL_ARRAY_BUFFER, "GL_ARRAY_BUFFER"},
    {GL_ELEMENT_ARRAY_BUFFER, "GL_ELEMENT_ARRAY_BUFFER"}
};

enum BufferUsage {
    RCN_VX,
    RCN_COLOR,
    RCN_UNUSED
};

struct BufferData
{
    GLenum bind_target;
    BufferUsage usage = RCN_UNUSED;
    std::size_t n = 0;
    std::size_t size = 0;
    unsigned int dataCount = 0;
};

namespace rcn3d {

/* Bufor powinien być raz stworzony,
 * funkcją createVertexBuffers, i raz usunięty via deleteVertexBuffers.
 */

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

    inline void setUsage(BufferUsage us) {
        assert(binded < size);
        buf_data[binded].usage = us;
    }

    inline int getUsageID(BufferUsage us) {
        for(std::size_t i=0;i<size;++i) 
            if(buf_data[i].usage == us)
                return i;
        return -1;
    }

    inline BufferData getBufferData(std::size_t n) const {
        assert(n < size);
        return buf_data[n];
    }

    /* OpenGL Calls wrapper */

    inline void bufferData_gl(const GLvoid* data, std::size_t dataSize,
            GLenum usage = GL_STATIC_DRAW) {
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

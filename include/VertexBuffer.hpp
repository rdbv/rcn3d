#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#define GLEW_STATIC 
#include <GL/glew.h>
#include <cstdint>
#include <cassert>

namespace rcn3d {

template<std::size_t N>
class VertexBuffer
{   
public:
    VertexBuffer() {
    }

    inline void createVertexBuffers() {
        glGenBuffers(N, buf);
    }

    void deleteBuffers() {
        glDeleteBuffers(N, buf);
    }

    void bind(GLenum t, std::size_t n) {
        assert(n < N);
        glBindBuffer(t, buf[n]); 
    }


private:

    GLuint buf[N];
    std::size_t size = N;
};

} // namespace rcn3d

#endif

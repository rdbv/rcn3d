#include "../include/VertexArray.hpp"
using namespace rcn3d;

void VertexArray::createVertexArrays() {
#ifdef VAO_DEBUG_PRINTF
    printf("[%s] size:%lu\n", __FUNCTION__, size);
#endif
    glGenVertexArrays(size, &vx[0]); 
}

void VertexArray::deleteVertexArrays() {
#ifdef VAO_DEBUG_PRINTF
    printf("[%s] size:%lu\n", __FUNCTION__, size);
#endif
    glDeleteVertexArrays(size, &vx[0]);
}

void VertexArray::bind(std::size_t n) {
    assert(n < size);
    glBindVertexArray(vx[n]);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

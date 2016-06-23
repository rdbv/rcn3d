#include "../include/VertexArray.hpp"
using namespace rcn3d;

void VertexArray::createVertexArrays() {
    glGenVertexArrays(size, &vx[0]); 
}

void VertexArray::deleteVertexArrays() {
    glDeleteVertexArrays(size, &vx[0]);
}

void VertexArray::bind(std::size_t n) {
    assert(n < size);
    glBindVertexArray(vx[n]);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

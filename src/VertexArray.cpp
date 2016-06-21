#include "../include/VertexArray.hpp"
using namespace rcn3d;

GLuint VertexArray::getID() {
    return obj;
}

void VertexArray::createVertexArray() {
    glGenVertexArrays(1, &obj); 
}

void VertexArray::deleteVertexArray() {
    glDeleteVertexArrays(1, &obj);
}

void VertexArray::bind() {
    glBindVertexArray(obj);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

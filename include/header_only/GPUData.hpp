#ifndef GPUDATA_HPP
#define GPUDATA_HPP

#include "../VertexArray.hpp"
#include "../VertexBuffer.hpp"

namespace rcn3d {

typedef std::shared_ptr<VertexArray>   VAO_SharedPtr;
typedef std::shared_ptr<VertexBuffer>  VBO_SharedPtr;

struct GPUData {
    VAO_SharedPtr vao_ptr;
    VBO_SharedPtr vbo_ptr;
};

} // namespace rcn3d

#endif

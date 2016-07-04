#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "../Transform.hpp"
#include "../Renderer.hpp"
#include "../ShaderProgram.hpp"

#include "VertexArray.hpp"

namespace rcn3d {

class Renderable : public Transform {

public:
    
    inline void setVertexArray(VertexArray* vao) {
        vao_data = vao;
    }

    inline void setShader(ShaderProgram* shdr) {
        shader = shdr;
    }

    inline VertexArray* getVertexArray() {
        return vao_data;
    }

    inline ShaderProgram* getShader() {
        return shader;
    }


private:
    VertexArray*   vao_data = nullptr;
    ShaderProgram* shader   = nullptr;    
};

} // namespace rcn3d

#endif

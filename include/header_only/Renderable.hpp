#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "../Transform.hpp"
#include "../Renderer.hpp"

#include "VertexArray.hpp"

namespace rcn3d {

class Renderable : public Transform {

public:
    
    void setVertexArray(VertexArray vao) {
        vao_data = vao;
    }


private:
    VertexArray vao_data;
    
};

} // namespace rcn3d

#endif

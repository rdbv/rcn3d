#ifndef RCN3D_OBJECTDATA_HPP
#define RCN3D_OBJECTDATA_HPP

#include <vector>
#include <glm/glm.hpp>

namespace rcn3d {
    struct ObjectData {
        std::vector <glm::vec3> vx;
        std::vector <glm::vec2> uv;
        std::vector <glm::vec3> vn;
        std::vector <std::vector <glm::ivec3>> faces;
    };
}

#endif //RCN3D_OBJECTDATA_H

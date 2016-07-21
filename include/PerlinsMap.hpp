#ifndef RCN3D_MAP_HPP
#define RCN3D_MAP_HPP

#include <vector>
#include <glm/glm.hpp>

namespace rcn3d {

class PerlinsMap {

public:
    PerlinsMap();

    ~PerlinsMap();

    void generateMap(unsigned int w, unsigned int h, float s, int o, float p, float l);

private:
    std::vector <int> mapData;
    unsigned int width;
    unsigned int height;
	float scale;
};
}
#endif //RCN3D_MAP_HPP

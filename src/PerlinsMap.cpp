#include "../include/PerlinsMap.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <cmath>
#include <fstream>

rcn3d::PerlinsMap::PerlinsMap() {

}

rcn3d::PerlinsMap::~PerlinsMap() {

}

void rcn3d::PerlinsMap::generateMap(int width, int height, float scale) {

    this->width = width;
    this->height = height;

//    std::ofstream outf("ddd.ppm", std::ios::out | std::ios::binary);
//    outf << "P6\n" << width << " " << height << "\n255\n";

    Canvas can;
    can.make(width, height);

    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float sampleX = j / scale;
            float sampleY = i / scale;

            float perlinValue = glm::perlin(glm::vec2(sampleX, sampleY)) + 1.0f;
            perlinValue = fmod(perlinValue, 1.0f);
            float lerpValue = glm::lerp(0.0f, 255.0f, perlinValue);
            can.setColor(j, i, lerpValue, lerpValue, lerpValue);

            mapData.push_back(perlinValue);
        }
    }
    can.save("perlin100x100.bmp");

}

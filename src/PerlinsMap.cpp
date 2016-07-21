#include "../include/PerlinsMap.hpp"

#include <glm/gtc/noise.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <cmath>
#include "../include/header_only/BmpGenerator.hpp"

rcn3d::PerlinsMap::PerlinsMap() {

}

rcn3d::PerlinsMap::~PerlinsMap() {

}

void rcn3d::PerlinsMap::generateMap(unsigned int w, unsigned int h, float s, int o, float p, float l) {

    width = w;
    height = h;
	scale = s;

	if(scale <= 0) {
		scale = 0.0001f;
	}

	rcn3d::Canvas can;
    can.make(width, height);

    for(int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

			float amplitude = 1.0f;
			float frequency = 1.0f;
			float noiseHeight = 0.0f;

			for(int i = 0; i < o; i++) {
				float sampleX = x / scale * frequency;
				float sampleY = y / scale * frequency;

				// Little hack since glm::perlin return number between -1.0f and 1.0f
				float perlinValue = glm::perlin(glm::vec2(sampleX, sampleY)) + 1.0f;
				perlinValue = static_cast<float>(fmod(perlinValue, 1.0f));
				noiseHeight += perlinValue * amplitude;

				amplitude *= p;
				frequency *= l;
			}

			int lerpValue = static_cast<int>(glm::lerp(0.0f, 255.0f, noiseHeight));
			can.setColor(x, y, lerpValue, lerpValue, lerpValue);
			mapData.push_back(lerpValue);
        }
    }
    can.save("perlin_noise_new.bmp");
}

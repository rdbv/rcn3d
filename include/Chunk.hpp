#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "header_only/Math.hpp"
#include "header_only/SDL_GLEW.hpp"

#include <vector>

typedef glm::tvec4<GLbyte> byte4;

#define CX 1
#define CY 1
#define CZ 1

namespace rcn3d {


class Chunk
{
public:
    void init_chunk(float x, float y, float z);
    void destroy_chunk();

    void generate();
    void render();

	glm::mat4& getMatrix() {return chunk_matrix;}

private:
    GLuint vbo;
    GLuint vx_count;
	glm::mat4 chunk_matrix;
};

};


#endif

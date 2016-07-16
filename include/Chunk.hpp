#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "header_only/Math.hpp"
#include "header_only/SDL_GLEW.hpp"

#include <vector>

typedef glm::tvec4<GLbyte> byte4;

#define CX 4
#define CY 4
#define CZ 4

namespace rcn3d {


class Chunk
{
public:
    void init_chunk();
    void destroy_chunk();

    void generate();
    void render();

private:
    GLuint vbo;
    GLuint vx_count;
};

};


#endif

#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "header_only/Math.hpp"
#include "header_only/SDL_GLEW.hpp"

#include <vector>

typedef glm::tvec4<GLbyte> byte4;

#define CX 10
#define CY 10
#define CZ 10

enum BlockType {
    BLOCK_AIR = 0,
    BLOCK_DIRT,
    BLOCK_DIRT_WITH_GRASS,
    BLOCK_GRASS,
    BLOCK_LEAF,
    BLOCK_WOOD,
    BLOCK_STONE,
    BLOCK_SAND,
    BLOCK_WATER,
    BLOCK_GLASS,
    BLOCK_BRICKS,
    BLOCK_CARBON,
    BLOCK_TREE_UP,
    BLOCK_WHITE, 
    BLOCK_BLACK,
    BLOCK_YX,
    BLOCK_END,
};

namespace rcn3d {


class Chunk
{
public:
    void init_chunk(float x, float y, float z);
    void destroy_chunk();

    void generate();
    void render();

    void set_block_type(std::size_t, std::size_t, std::size_t, BlockType);

	glm::mat4& getMatrix() {return chunk_matrix;}

private:
    GLuint vbo;
    GLuint vx_count;
    BlockType blocks[CX][CY][CZ];
	glm::mat4 chunk_matrix;
};

};


#endif

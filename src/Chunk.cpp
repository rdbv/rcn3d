#include "../include/Chunk.hpp"

using namespace rcn3d;

void Chunk::init_chunk(float x, float y, float z) {
    memset(blocks, 0, sizeof(blocks));
    glGenBuffers(1, &vbo);
    chunk_matrix = glm::translate(glm::mat4(1), glm::vec3(x, y, z));
}

void Chunk::destroy_chunk() {
    glDeleteBuffers(1, &vbo);
}

void Chunk::generate() {
    std::vector<byte4> vx; 

    /* -x czyli generowanie lewej sciany chunka
     * zlozonej z trójkątnych scian, na 1 sciane przypadaja 2 trojkaty
     * czyli 6 vx :)
     * side to material
     */
    int side = BLOCK_AIR;
    // -x
    for(int x = CX - 1; x >= 0; x--) {
        for(int y = 0; y < CY; y++) {
            for(int z = 0; z < CZ; z++) {
                side = blocks[x][y][z];
                vx.push_back(byte4(x, y, z, side));
                vx.push_back(byte4(x, y, z + 1, side));
                vx.push_back(byte4(x, y + 1, z, side));
                vx.push_back(byte4(x, y + 1, z, side));
                vx.push_back(byte4(x, y, z + 1, side));
                vx.push_back(byte4(x, y + 1, z + 1, side));
            }
        }
    }

    // +x
    for(int x = 0;x < CX; x++) {
        for(int y = 0; y < CY; y++) {
            for(int z = 0; z < CZ; z++) {
                side = blocks[x][y][z];
                vx.push_back(byte4(x + 1, y, z, side));
                vx.push_back(byte4(x + 1, y + 1, z, side));
                vx.push_back(byte4(x + 1, y, z + 1, side));
                vx.push_back(byte4(x + 1, y + 1, z, side));
                vx.push_back(byte4(x + 1, y + 1, z + 1, side));
                vx.push_back(byte4(x + 1, y, z + 1, side));
            }
        }
    }

    // -y
    uint8_t side_down = 0;
    for(int x = 0; x < CX; x++) {
        for(int y = CY - 1; y >= 0; y--) {
            for(int z = 0; z < CZ; z++) {
                side = blocks[x][y][z];            
                side_down = side + 128;
                vx.push_back(byte4(x, y, z, side_down));
                vx.push_back(byte4(x + 1, y, z, side_down));
                vx.push_back(byte4(x, y, z + 1, side_down));
                vx.push_back(byte4(x + 1, y, z, side_down));
                vx.push_back(byte4(x + 1, y, z + 1, side_down));
                vx.push_back(byte4(x, y, z + 1, side_down));
            } 
        }
    }


    // +y
    uint8_t side_up = 0;
    for(int x = 0; x < CX; x++) {
        for(int y = 0; y < CY; y++) {
            for(int z = 0; z < CZ; z++) {
                side = blocks[x][y][z];
                side_up = side + 128;
                vx.push_back(byte4(x, y + 1, z, side_up));
                vx.push_back(byte4(x, y + 1, z + 1, side_up));
                vx.push_back(byte4(x + 1, y + 1, z, side_up));
                vx.push_back(byte4(x + 1, y + 1, z, side_up));
                vx.push_back(byte4(x, y + 1, z + 1, side_up));
                vx.push_back(byte4(x + 1, y + 1, z + 1, side_up));
            }
        }
    }

    // -z    
    for(int x = 0; x < CX; x++) {
        for(int z = CZ - 1; z >= 0; z--) {
            for(int y = 0; y < CY; y++) {
                side = blocks[x][y][z];
                vx.push_back(byte4(x, y, z, side));
                vx.push_back(byte4(x, y + 1, z, side));
                vx.push_back(byte4(x + 1, y, z, side));
                vx.push_back(byte4(x, y + 1, z, side));
                vx.push_back(byte4(x + 1, y + 1, z, side));
                vx.push_back(byte4(x + 1, y, z, side));
            }
        }
    }

    // +z
    for(int x = 0; x < CX; x++) {
        for(int z = 0; z < CZ; z++) {
            for(int y = 0; y < CY; y++) {
                side = blocks[x][y][z];
                vx.push_back(byte4(x, y, z + 1, side));
                vx.push_back(byte4(x + 1, y, z + 1, side));
                vx.push_back(byte4(x, y + 1, z + 1, side));
                vx.push_back(byte4(x, y + 1, z + 1, side));
                vx.push_back(byte4(x + 1, y, z + 1, side));
                vx.push_back(byte4(x + 1, y + 1, z + 1, side));
            }
        }
    }

    vx_count = vx.size();   
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vx.size() * sizeof(byte4), &vx[0], GL_STATIC_DRAW);
}

void Chunk::render() {

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, vx_count);

}

void Chunk::set_block_type(std::size_t x, std::size_t y, std::size_t z, BlockType bt) {
    assert(x < CX); 
    assert(y < CY); 
    assert(z < CZ);
    assert(bt < BLOCK_END);
    blocks[x][y][z] = bt;
}


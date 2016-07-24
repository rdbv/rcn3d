#include "../include/Chunk.hpp"

using namespace rcn3d;

void Chunk::init_chunk(float x, float y, float z) {
    glGenBuffers(1, &vbo);
    chunk_matrix = glm::translate(glm::mat4(1), glm::vec3(x, y, z));
}

void Chunk::destroy_chunk() {
    glDeleteBuffers(1, &vbo);
}

void Chunk::generate() {
    std::vector<byte4> vx; 

    int side = 0;
    // -x
    for(int x = CX - 1; x >= 0; x--) {
        for(int y = 0; y < CY; y++) {
            for(int z = 0; z < CZ; z++) {
                vx.push_back(byte4(x, y, z, side));
                vx.push_back(byte4(x, y, z + 1, side));
                vx.push_back(byte4(x, y + 1, z, side));
                vx.push_back(byte4(x, y + 1, z, side));
                vx.push_back(byte4(x, y, z + 1, side));
                vx.push_back(byte4(x, y + 1, z + 1, side));
            }
        }
    }

    side = 1;
    // +x
    for(int x = 0;x < CX; x++) {
        for(int y = 0; y < CY; y++) {
            for(int z = 0; z < CZ; z++) {
                vx.push_back(byte4(x + 1, y, z, side));
                vx.push_back(byte4(x + 1, y + 1, z, side));
                vx.push_back(byte4(x + 1, y, z + 1, side));
                vx.push_back(byte4(x + 1, y + 1, z, side));
                vx.push_back(byte4(x + 1, y + 1, z + 1, side));
                vx.push_back(byte4(x + 1, y, z + 1, side));
            }
        }
    }

    side = 2;
    // -y
    for(int x = 0; x < CX; x++) {
        for(int y = CY - 1; y >= 0; y--) {
            for(int z = 0; z < CZ; z++) {
                vx.push_back(byte4(x, y, z, side));
                vx.push_back(byte4(x + 1, y, z, side));
                vx.push_back(byte4(x, y, z + 1, side));
                vx.push_back(byte4(x + 1, y, z, side));
                vx.push_back(byte4(x + 1, y, z + 1, side));
                vx.push_back(byte4(x, y, z + 1, side));
            } 
        }
    }


    side = 3;
    // +y
    for(int x = 0; x < CX; x++) {
        for(int y = 0; y < CY; y++) {
            for(int z = 0; z < CZ; z++) {
                vx.push_back(byte4(x, y + 1, z, side));
                vx.push_back(byte4(x, y + 1, z + 1, side));
                vx.push_back(byte4(x + 1, y + 1, z, side));
                vx.push_back(byte4(x + 1, y + 1, z, side));
                vx.push_back(byte4(x, y + 1, z + 1, side));
                vx.push_back(byte4(x + 1, y + 1, z + 1, side));
            }
        }
    }

    side = 4;
    // -z    
    for(int x = 0; x < CX; x++) {
        for(int z = CZ - 1; z >= 0; z--) {
            for(int y = 0; y < CY; y++) {
                vx.push_back(byte4(x, y, z, side));
                vx.push_back(byte4(x, y + 1, z, side));
                vx.push_back(byte4(x + 1, y, z, side));
                vx.push_back(byte4(x, y + 1, z, side));
                vx.push_back(byte4(x + 1, y + 1, z, side));
                vx.push_back(byte4(x + 1, y, z, side));
            }
        }
    }

    side = 5;
    // +z
    
    for(int x = 0; x < CX; x++) {
        for(int z = 0; z < CZ; z++) {
            for(int y = 0; y < CY; y++) {
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


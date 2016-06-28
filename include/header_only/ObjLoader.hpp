#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

using namespace rcn3d;

#include <cstdio>
#include <cstring>
#include <vector>
#include <glm/glm.hpp>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

#define BUFFER_LENGTH 128

namespace rcn3d {

struct ObjectData {

    std::vector<glm::vec3> vx;
    std::vector<glm::vec3> uv;
    std::vector<glm::vec3> normals;
    char name[BUFFER_LENGTH];
    bool isUVIncluded;

};


class ObjLoader 
{
public:

    bool loadObj(const char* path, VertexArray& m_vao) {
        
        VertexBuffer m_vbo;

        m_vao.createVertexArrays(1);
        m_vbo.createVertexBuffers(2)        
    }

    bool loadObjData(const char* path, ObjectData& dat) {
        FILE* f = fopen(path, "r");
        char line[BUFFER_LENGTH];

        if(!f) {
            printf("Failed to load %s\n", path);
            return false;
        }

        char fc, c1;
        float x, y, z;

        while(fgets(line, BUFFER_LENGTH, f) != NULL) {
            fc = line[0];            
            c1 = line[1];

            if(fc == '#')
                continue;
            
            if(fc == 's')
                continue;

            if(fc == 'o') {
                sscanf(line+2, "%s", dat.name);
            }

            if(fc == 'v' && (c1 != 't' && c1 != 'n') ) {
                sscanf(line+2, "%f %f %f\n", &x, &y, &z); 
                dat.vx.push_back(glm::vec3(x, y, z));
            }
             
            if(fc == 'v' && c1 == 't') {
                sscanf(line+3, "%f %f %f", &x, &y, &z);
                dat.uv.push_back(glm::vec3(x, y, z));
            }

            if(fc == 'v' && c1 == 'n') {
                sscanf(line+3, "%f %f %f", &x, &y, &z);
                dat.normals.push_back(glm::vec3(x, y, z));
            }
            
            if(fc =='f') {
                char* beg = line+2;
                char* sls_beg  = strchr(beg, '/');

                if(!sls_beg)
                    return false;

                dat.isUVIncluded = sls_beg[0] != sls_beg[1]; 

                if(dat.isUVIncluded) {
                }


            }

        }

        return true;
    }
};

} // namespace rcn3d

#endif

#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP


#include <cstdio>
#include <cstring>
#include <vector>
#include <glm/glm.hpp>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

#define BUFFER_LENGTH 128

namespace rcn3d {

    using namespace rcn3d;

struct ObjectData {

    std::vector<glm::vec3> vx;
    std::vector<glm::vec3> uv;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> vx_ebo, uv_ebo, normals_ebo;

    char name[BUFFER_LENGTH];
    bool isUVIncluded;

};


class ObjLoader 
{
public:

    bool loadObj(const char* path, VertexArray& m_vao) {
        
        VertexBuffer m_vbo;

        //m_vao.createVertexArrays(1);
        //m_vbo.createVertexBuffers(2);

        return false;
    }

    bool loadObjData(const char* path, ObjectData& dat) {
        FILE* f = fopen(path, "r");
        char line[BUFFER_LENGTH];
        std::vector<glm::vec3>* data_ptr = nullptr;

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
                unsigned int data[9];

                if(!sls_beg)
                    return false;

                dat.isUVIncluded = sls_beg[0] != sls_beg[1]; 
                               
                
                                        
                if(dat.isUVIncluded) {

                sscanf(beg, "%d/%d/%d %d/%d/%d %d/%d/%d", &data[0], &data[1], &data[2], 
                                                          &data[3], &data[4], &data[5], 
                                                          &data[6], &data[7], &data[8]);

                }
                else {
                    sscanf(beg, "%d//%d %d//%d %d//%d", &data[0], &data[2],
                                                        &data[3], &data[5],
                                                        &data[6], &data[8]);
                                                        
                }



            }

        }

        return true;
    }

};

} // namespace rcn3d

#endif

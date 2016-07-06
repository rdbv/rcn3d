#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP


#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

#define BUFFER_LENGTH 128

namespace rcn3d {

    using namespace rcn3d;

struct ObjectData {

    std::vector<glm::vec3> vx;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> vn;
    std::vector <std::vector <glm::ivec3>> faces;
};


class ObjLoader 
{
public:

    bool loadObjData(const std::string& filePath) {
        // Check file extension
        auto p = filePath.end();
        if(!(*p == 'j' && *(p - 1) == 'b' && *(p - 2) == 'o')) {
            printf("File has wrong extension!\n");
            return false;
        }

        // Open file and check if succeed
        std::ifstream f(filePath);
        if(f.fail()) {
            printf("Could not load .obj file. Wrong file path\n");
            return false;
        }

        std::string buf;
        ObjectData obj;
        float x, y, z;
        float u, v;
        while(!f.eof()) {
            f >> buf;
            // Skip if current line is comment
            if(buf[0] == '#') {
                std::getline(f, buf);
                continue;
            }

            if(buf == "usemtl") {
                std::string materialPath;
                f >> materialPath;
                //TODO use material in given path
            } else if(buf == "v") {
                f >> x >> y >> z;
                obj.vx.emplace_back(glm::vec3(x, y, z));
            } else if(buf == "vt") {
                f >> u >> v;
                obj.uv.emplace_back(glm::vec2(u, v));
            } else if(buf == "vn") {
                f >> x >> y >> z;
                obj.vn.emplace_back(glm::vec3(x, y, z));
            } else if(buf == "f") {
                std::getline(f, buf);
                parseFaces(obj.faces, buf);
            } else {
                printf("Unknown sytanx in .obj file\n");
            }
        }
        return true;
    }


private:
    void parseFaces(std::vector <std::vector<glm::ivec3>>& faces, std::string& s) {
        std::vector <glm::ivec3> v;
        v.reserve(3);
        int x;

        std::string t = "";
        int c = 0;
        std::size_t c2 = 0;
        for(std::size_t i = 0; i < s.size(); i++) {
            if(s[i] != '/') {
                t += s[i];
            } else {
                x = std::atoi(t.c_str());
                if(c == 0) {
                    v[c2].x = x;
                } else if(c == 1) {
                    v[c2].y = x;
                } else if(c == 2) {
                    v[c2].z = x;
                    c2++;
                    c = -1;
                }
                c++;
                t = "";
            }
        }
        faces.push_back(v);
    }

};

} // namespace rcn3d

#endif

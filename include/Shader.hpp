#ifndef SHADER_HPP
#define SHADER_HPP

#define GLEW_STATIC 
#include <GL/glew.h>

#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <stdexcept>

#define INFO_LOG_SIZE 512 * 4
#define __SHADER_DEBUG_INFO_DUMP

namespace rcn3d {

static auto getFileSizeInBytes = [](FILE *f) {
    long size = 0;
    fseek(f, 0L, SEEK_END);
    size = ftell(f);
    fseek(f, 0L, SEEK_SET);
    return size;
};

static auto getFileAsString = [](const std::string& path) {
    FILE* f = fopen(path.c_str(), "rb");
    long sizeBytes = 0;
    if(f == nullptr)
        throw std::runtime_error("Unable to open file " + path);

    sizeBytes = rcn3d::getFileSizeInBytes(f);

    std::vector<GLchar> code;
    code.resize(sizeBytes+1);

    if(fread(&code[0], sizeBytes, 1, f) != 1)
        throw std::runtime_error("Unable to read " + path);

    code[sizeBytes] = '\x00';

    return std::string(code.begin(), code.end());
};

static auto isValidShaderType = [](const GLenum& type) {
    return ( type == GL_VERTEX_SHADER   ||
             type == GL_FRAGMENT_SHADER ||
             type == GL_GEOMETRY_SHADER );
};

static auto getShaderNameString = [](const GLenum& type) {
    if( type == GL_VERTEX_SHADER )   return "VertexShader";
    if( type == GL_FRAGMENT_SHADER ) return "FragmentShader";
    if( type == GL_GEOMETRY_SHADER ) return "GeometryShader";

    throw std::runtime_error("hmm???");
    /* Should not happen */
};

class Shader {

public:

    Shader(const GLenum&);

    bool loadFromFile(const std::string&);
    bool loadFromString(const std::string&);

    bool compile();
    void destroy();

    GLuint getProgramID() const;

private:
    GLuint pID = 0;
    GLenum shaderType;
    GLchar errorLog[INFO_LOG_SIZE];

    std::string shaderName;
    std::vector<GLchar> code;
};

} // namespace rcn3d

#endif

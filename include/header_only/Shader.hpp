#ifndef SHADER_HPP
#define SHADER_HPP

#include "SDL_GLEW.hpp"
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>

#include <glm/gtc/type_ptr.hpp>

#define INFO_LOG_SIZE 512 * 4
#define __SHADER_INFO_DUMP

template<typename T>
std::size_t size(const T& t) {
    return t.size() * sizeof(T);
}

static long get_file_size(FILE* f) {
    long size = 0;
    fseek(f, 0L, SEEK_END), size = ftell(f), fseek(f, 0L, SEEK_SET);
    return size;
};

static std::string get_file_as_string(const std::string& path) {
    FILE* f = fopen(path.c_str(), "rb");
    long size_bytes = 0;

    if(!f) {
        printf("Failed to open file %s\n", path.c_str());
        exit(0);
    }
    size_bytes = get_file_size(f);

    std::vector<GLchar> code;
    code.resize(size_bytes + 1);

    if(fread(&code[0], size_bytes, 1, f) != 1) {
        printf("Unable to read %s\n", path.c_str());
        exit(0);
    }

    code[size_bytes] = 0;
    return std::string(code.begin(), code.end());
}

static bool get_shader_typename(GLenum type, std::string& s) {
    if(type == GL_VERTEX_SHADER)   {s = "VertexShader"; return true;}
    if(type == GL_FRAGMENT_SHADER) {s = "FragmentShader"; return true;}
    s = "???";
    return false;
}

/* ++++++++++++++++++++++++++++++++ */

class Shader
{
public:
    
    inline bool compile(GLenum type, std::string path) {

        code = get_file_as_string(path);
        const GLchar* src = &code[0];
        GLchar error_log[INFO_LOG_SIZE];
        GLint success;

        glShaderSource(shaderID, 1, &src, NULL);
        glCompileShader(shaderID);
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        
        if(!success) {
            glGetShaderInfoLog(shaderID, INFO_LOG_SIZE, NULL, error_log);
            printf("[%s]: %s\n", type_name.c_str(), error_log);
            return false;
        }
        return true;
    }

    inline bool create_shader(GLenum type) {
        if(!get_shader_typename(type, type_name)) 
            return false;

        shaderID = glCreateShader(type);

        if(shaderID == 0) { 
            return false;
        }
        return true;         
    }
    
    inline void destroy_shader() {
        assert(shaderID != 0);
        glDeleteShader(shaderID);
    }

    inline GLuint get_shader_id() {
        return shaderID;
    }

private:
    GLuint shaderID;
    GLenum type;
    std::string code; 
    std::string type_name;
};

/* ++++++++++++++++++++++++++++++++ */

class ShaderProgram
{
public:

    bool load_shader(std::string vx, std::string fg) {
        Shader vertex, fragment;

        vertex.create_shader(GL_VERTEX_SHADER);
        fragment.create_shader(GL_FRAGMENT_SHADER);

        if(!vertex.compile(GL_VERTEX_SHADER, vx)) return false; 
        if(!fragment.compile(GL_FRAGMENT_SHADER, fg)) return false;

        programID = glCreateProgram();

        /* Attach shaders */
        glAttachShader(programID, vertex.get_shader_id());
        glAttachShader(programID, fragment.get_shader_id());

        /* Link and check */
        GLint link_status;

        glLinkProgram(programID);
        glGetProgramiv(programID, GL_LINK_STATUS, &link_status);
        if(link_status == GL_FALSE) {
            printf("Linking failed\n");
            exit(0);
        }

        vertex.destroy_shader();
        fragment.destroy_shader();

        return true;
    }

    void delete_program() {
        glDeleteProgram(programID);
    }

    GLint add_uniform(const std::string& name, bool unused = false) {
        GLint v = glGetUniformLocation(programID, name.c_str());
        if(v == -1) { 
            printf("Failed to get uni (%s) location\n", name.c_str());
            if(unused)
                return -1;
            else
                exit(0);
        }
        uniforms[name] = v;
        return v;        
    }

    template<typename T>
    inline void set_uniform(const std::string name, T&& val) {
        if(uniforms.count(name) == 0)
        {
            //printf("OyOyOy %s\n", name.c_str());
            return;
        }

        GLint loc = uniforms[name];
        set_uniform(loc, std::forward<T>(val));
    }

    inline void set_uniform(GLint loc, const float& v) {
        glUniform1f(loc, v);
    }

    inline void set_uniform(GLint loc, const glm::mat4& mx) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mx));
    }

    void run() {
        glUseProgram(programID);
    }

    void disable() {
        glUseProgram(0);
    }

private:
    GLuint programID;
    std::map<std::string, GLuint> uniforms;        
};

/* ++++++++++++++++++++++++++++++++ */

#endif

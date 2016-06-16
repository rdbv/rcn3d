#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#define GLEW_STATIC
#include "Shader.hpp"
#include "header_only/Math.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <unordered_map>
#include <initializer_list>

namespace rcn3d {

class ShaderProgram {
public:
    ShaderProgram() = delete;
    ShaderProgram(const std::string&, const std::string&);

    inline GLuint getProgram() {
        return pID;
    }

    std::unordered_map<std::string, GLuint> 
    addUniforms(const std::initializer_list<std::string>&);

    GLint addUniform(const std::string&);

    template<typename T>
    inline void setUniform(const std::string& name, T&& val) {
#ifdef __SHADER_CHECK_IS_UNIFORM_EXIST
        if(uniformsMap.count(name) == 0)
            return;
#endif
        GLint loc = uniformsMap[name];
        setUniform(loc, std::forward<T>(val));
    }

    inline void setUniform(GLint loc, const float& v) {
        glUniform1f(loc, v);
    }

    inline void setUniform(GLint loc, const int& v) {
        glUniform1i(loc, v);
    }

    inline void setUniform(GLint loc, const glm::mat4& mx) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mx));
    }

    inline void run() {
        glUseProgram(pID);
    }

    inline void disable() {
        glUseProgram(0);
    }

    ~ShaderProgram();

private:
    void attachShader(const Shader&);
    void linkProgram();

    GLuint pID = 0;
    GLuint shaderCount = 0;
    std::unordered_map<std::string, GLint> uniformsMap;
};

} // namespace rcn3d

#endif

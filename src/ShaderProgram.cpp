#include "../include/ShaderProgram.hpp"

rcn3d::ShaderProgram::ShaderProgram(const std::string& pathVertex,
                                    const std::string& pathFragment
                                   /*, here will be geo-shdr path */ ) {
    load(pathVertex, pathFragment);
}

void rcn3d::ShaderProgram::load(const std::string& pathVertex, const std::string& pathFragment) {
    pID = glCreateProgram();
    #ifdef __SHADER_DEBUG_INFO_DUMP
        printf("[ShaderProgram::ShaderProgram] Created program %d\n", pID);
    #endif

    rcn3d::Shader vx(GL_VERTEX_SHADER);
    rcn3d::Shader fg(GL_FRAGMENT_SHADER);

    vx.loadFromFile(pathVertex), fg.loadFromFile(pathFragment);
    attachShader(vx), attachShader(fg);

    linkProgram();

    vx.destroy(), fg.destroy();
}

void rcn3d::ShaderProgram::attachShader(const Shader &shader) {
    glAttachShader(pID, shader.getProgramID());
    ++shaderCount;
}

void rcn3d::ShaderProgram::linkProgram() {
    if(shaderCount >= 2) {
        glLinkProgram(pID);
        GLint linkStatus;

        glGetProgramiv(pID, GL_LINK_STATUS, &linkStatus);

        /* If linking OK, we can delete fragment and vertex shaders */
        if(linkStatus == GL_FALSE)
            throw std::runtime_error("Failed to link shaders\n");

    }
    else
        throw std::runtime_error("Unable to link, too li'l shaders attached :-/\n");
}

GLint rcn3d::ShaderProgram::addUniform(const std::string& name) {
    GLint v = glGetUniformLocation(pID, name.c_str());

    if(v == -1)
        throw std::runtime_error("Failed to get uniform (" + name + ") location\n");

    uniformsMap[name] = v;
    return v;
}

std::unordered_map<std::string, GLuint>
rcn3d::ShaderProgram::addUniforms(const std::initializer_list<std::string>& lst) {

    std::unordered_map<std::string, GLuint> uniforms;
    for(const auto& uni : lst) {
        GLint v = glGetUniformLocation(pID, uni.c_str());
        if(v == -1)
            throw std::runtime_error("Failed to get uniform (" + uni + "} location\n");
        uniforms[uni] = v;
        uniformsMap[uni] = v;
    }
    return uniforms;
}

rcn3d::ShaderProgram::~ShaderProgram() {
    glDeleteProgram(pID);
#ifdef __SHADER_DEBUG_INFO_DUMP
    printf("[ShaderProgram::~ShaderProgram] Deleted program %d\n", pID);
#endif
}

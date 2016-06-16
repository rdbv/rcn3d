#include "../include/Shader.hpp"

rcn3d::Shader::Shader(const GLenum& type) {

    if(!isValidShaderType(type))
        throw std::runtime_error("Bad shader type\n");

    shaderType = type;
    shaderName = getShaderNameString(type);
}

bool rcn3d::Shader::loadFromFile(const std::string& path) {
    auto s = getFileAsString(path);
    code = std::vector<GLchar>(s.begin(), s.end());    
    return compile();
}

bool rcn3d::Shader::loadFromString(const std::string& codeShader) {
    long len = codeShader.length();
    memcpy(&code[0], &codeShader[0], len);
    return compile();
}

bool rcn3d::Shader::compile() {

    const GLchar* source = &code[0];
    GLint success;

    /* Generate shader object */
    pID = glCreateShader(shaderType);

#ifdef __SHADER_DEBUG_INFO_DUMP
    printf("[Shader::compile] Created %d shader\n", pID);
#endif

    /* Check is pID valid object */
    if(pID == 0) {
#ifdef FATAL_ERROR_DUMP_AND_QUIT
        printf("Failed to create shader object, quitting\n");
        exit(0);
#endif
        return false;
    }

    glShaderSource(pID, 1, &source, NULL);
    glCompileShader(pID);
    glGetShaderiv(pID, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(pID, INFO_LOG_SIZE, NULL, errorLog);
        printf("[%s]: %s\n", shaderName.c_str(), errorLog);
        return false;
    }

    return true;
}

void rcn3d::Shader::destroy() {
    assert(pID != 0);
#ifdef __SHADER_DEBUG_INFO_DUMP
    printf("[Shader::destroy] Deleted %d shader\n", pID);
#endif
    glDeleteShader(pID);
}

GLuint rcn3d::Shader::getProgramID() const {
    return pID;
}

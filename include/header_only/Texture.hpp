#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <cassert>

namespace rcn3d {

class Texture 
{
public:

    inline void createTexture() {
        glGenTextures(1, &texID);
    }

    inline void deleteTexture() {
        glDeleteTextures(1, &texID);        
    }

    inline void bind(GLenum t) {
        type = t;
        glBindTexture(t, texID);
    }

    inline void bindAndActivate(GLenum slot) {
        assert(type != GL_INVALID_ENUM);
        glActiveTexture(slot);
        glBindTexture(type, texID);
    }

private:
    GLuint texID = 0;
    GLenum type  = GL_INVALID_ENUM;
};

} // namespace rcn3d

#endif

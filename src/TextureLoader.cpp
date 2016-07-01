#include "../include/TextureLoader.hpp"

using namespace rcn3d;

Texture TextureLoader::loadNormalTexture(std::string name) {

    Texture t;
    t.createTexture();
    t.bind(GL_TEXTURE_2D);

    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(name.c_str(), 0);
    if(format == -1) {
        printf("Failed to read format @ %s\n", name.c_str());
        exit(0);
    }

    FIBITMAP* bitmap = FreeImage_Load(format, name.c_str());
    FIBITMAP* bitmap32 = nullptr;

    int bpp = FreeImage_GetBPP(bitmap);

    if(bpp == 32) {
        bitmap32 = bitmap;
    }
    else {
        bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
    }

    int width = FreeImage_GetWidth(bitmap32);
    int height = FreeImage_GetHeight(bitmap32);

    GLubyte* texdata = FreeImage_GetBits(bitmap32);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 width,
                 height,
                 0, 
                 GL_BGRA,
                 GL_UNSIGNED_BYTE,
                 texdata);

    FreeImage_Unload(bitmap32);
    if(bpp != 32) {
        FreeImage_Unload(bitmap);
    }

    return t;
}


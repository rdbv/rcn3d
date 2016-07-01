#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP

#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL/SDL.h>
#else
#endif
#include <string>
#include <FreeImage.h>
#include <cstdio>
#include <map>
#include <functional>

#include "header_only/Texture.hpp"

namespace rcn3d {

class TextureLoader
{
public:
    Texture loadNormalTexture(std::string);

private:
    Texture* checkForExistingTexture(std::string);

    std::map <Uint32, Texture*> textureMap;

};

} // namespace rcn3d

#endif

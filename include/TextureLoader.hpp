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

#include "header_only/Texture.hpp"

namespace rcn3d {

class TextureLoader
{
public:
    Texture loadNormalTexture(const std::string&);
       
};

} // namespace rcn3d

#endif

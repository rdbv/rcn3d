#ifndef SDL_GLEW_HPP
#define SDL_GLEW_HPP

#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL/SDL.h>
#else
#endif

#ifdef _WIN32
#define GLEW_STATIC
#endif

#include <GL/glew.h>

#endif

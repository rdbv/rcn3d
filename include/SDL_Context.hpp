#ifndef SDL_WINDOW_HPP
#define SDL_WINDOW_HPP

#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#else
#endif

#include <GL/glew.h>

#include "header_only/Math.hpp"

#include <string>
#include <stdexcept>
#include <cassert>

#define WINDOW_CENTERED -1

#define DEFAULT_WINDOW_X 800
#define DEFAULT_WINDOW_Y 600
#define DEFAULT_WINDOW_XPOS WINDOW_CENTERED
#define DEFAULT_WINDOW_YPOS WINDOW_CENTERED

namespace rcn3d {

/* Get error in format
 * SDL Error (<function_name>) : <SDL_error>
 */
auto build_SDL_errorstr = []() {
    std::string errorString;
    errorString += "SDL Error (";
    errorString += __func__;
    errorString += ") : ";
    errorString += SDL_GetError();
    return errorString;
};

/* SDL Window and Context settings */
struct SDL_Settings {
    std::string windowName = "rcn3d";
    glm::vec2 windowSize = glm::vec2(DEFAULT_WINDOW_X, DEFAULT_WINDOW_Y);
    glm::vec2 windowPos = glm::vec2(DEFAULT_WINDOW_XPOS, DEFAULT_WINDOW_XPOS);
};

/* Whole SDL Context - Window and OpenGL context */
class SDL_Context
{
public:

    /* Get SDL Window handler */
    inline SDL_Window* getWindow() {
        return window;
    }

    /* Init whole SDL */
    void initContext(SDL_Settings cSettings = SDL_Settings() );

    /* Swap SDL buffers*/
    void swapBuffers();

    /* Cleanup SDL */
    void destroy();

    ~SDL_Context();

private:

    /* Set SDL settings */
    bool initWindowSDL(SDL_Settings);
    /* Set OpenGL settings */
    bool initGLContextSDL(SDL_Settings);

    SDL_Window* window       = nullptr;
    SDL_GLContext glContext;
};

}; // namespace rcn3d

#endif

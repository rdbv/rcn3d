#include "../include/SDL_Context.hpp"

using namespace rcn3d;

void SDL_Context::initContext(SDL_Settings cSettings) {

    if(!initWindowSDL(cSettings))
        throw std::runtime_error(build_SDL_errorstr());

    if(!initGLContextSDL(cSettings))
        throw std::runtime_error(build_SDL_errorstr());

}

void SDL_Context::swapBuffers() {
    SDL_GL_SwapWindow(window);
}

void SDL_Context::destroy() {
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool SDL_Context::initWindowSDL(SDL_Settings cSettings) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;

    // if windowPos < 0, window will be placed on screen center
    auto xPos = cSettings.windowPos.x() < 0 ? SDL_WINDOWPOS_CENTERED : cSettings.windowPos.x();
    auto yPos = cSettings.windowPos.y() < 0 ? SDL_WINDOWPOS_CENTERED : cSettings.windowPos.y();

    // create SDL window
    window = SDL_CreateWindow(
            cSettings.windowName.c_str(),
            xPos,
            yPos,
            cSettings.windowSize.x(),
            cSettings.windowSize.y(),
            SDL_WINDOW_OPENGL);

    // check errors
    if(!window)
        return false;

    return true;
}

bool SDL_Context::initGLContextSDL(SDL_Settings cSettings) {
    glContext = SDL_GL_CreateContext(window);
    
    if(!glContext)
        return false;
     
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    glewExperimental = true;
    glewInit();

    return true;
}

SDL_Context::~SDL_Context() {
    assert(window != nullptr);
    destroy();
}




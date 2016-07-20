#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

#include "Math.hpp"
#include "SDL_GLEW.hpp"
#include "FrameTime.hpp"
#include "Camera.hpp"

#include <map>

typedef std::map<Uint32, bool> KeyMap;

#define WINDOW_SIZE glm::vec2(1300, 700)
#define WINDOW_POS  glm::vec2(50, 0)
#define WINDOW_NAME "OpenGL"

using namespace rcn3d;

class Window 
{
public:

    bool init_sdl(std::string window_name = WINDOW_NAME, 
                  glm::vec2 window_size = WINDOW_SIZE, 
                  glm::vec2 window_pos = WINDOW_POS) {

        win_siz = window_size, win_pos = window_pos;

        win = SDL_CreateWindow(window_name.c_str(),
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                window_size.x, window_size.y,
                SDL_WINDOW_OPENGL);
    
        SDL_SetRelativeMouseMode(SDL_TRUE);

        if(win == nullptr)
            return false;

        ctx = SDL_GL_CreateContext(win);
       
        SDL_GL_SetSwapInterval(1);
        GLenum glew_stat = glewInit();
        if(glew_stat != GLEW_OK)
            return false;

        return false;
    }

    void init_gl() {
        //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
        //SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        //glEnable(GL_MULTISAMPLE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void destroy_sdl() {
        SDL_GL_DeleteContext(ctx);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }

    SDL_Window* get_win_handle() {
        return win;
    }

    glm::vec2 get_init_pos() {
        return win_pos;
    }

    glm::vec2 get_init_size() {
        return win_siz;
    }

private:

   SDL_Window* win = nullptr;
   SDL_GLContext ctx;
   glm::vec2 win_siz, win_pos;

};

bool process_events(KeyMap& keys, 
                    DebugCamera& cam, 
                    FrameTime& ft) {

    SDL_Event ev;
    while(SDL_PollEvent(&ev)) {
        if(ev.type == SDL_KEYDOWN)
            keys[ev.key.keysym.sym] = true;
        if(ev.type == SDL_KEYUP)
            keys[ev.key.keysym.sym] = false;
        if(ev.type == SDL_MOUSEMOTION) {
            float x = ev.motion.xrel;
            float y = -ev.motion.yrel;
            cam.process_mouse(x, y);
        }
    }    

    bool quit = true;

    if(keys['q']) quit = false;
    if(keys['w']) cam.process_keyboard(FORWARD,  ft.getDeltaTime());
    if(keys['s']) cam.process_keyboard(BACKWARD, ft.getDeltaTime());
    if(keys['a']) cam.process_keyboard(LEFT,     ft.getDeltaTime());
    if(keys['d']) cam.process_keyboard(RIGHT,    ft.getDeltaTime());

    return quit;    

}

#endif

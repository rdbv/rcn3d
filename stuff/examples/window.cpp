#include "../../include/Engine.hpp"
#include <iostream>

int main() {

    rcn3d::Engine e;
    rcn3d::SDL_Settings set;

    e.context_SDL.initContext(set);

    while(true) {
        SDL_Event ev;

        while(SDL_PollEvent(&ev)) {
            if(ev.type == SDL_KEYDOWN) {
                if(ev.key.keysym.sym == 'q')
                    exit(0);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.25f, 0.0f, 0.0f, 0.0f);

        e.context_SDL.swapBuffers();
    }

    
}


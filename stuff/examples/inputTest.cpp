#include "../../include/Engine.hpp"
#include "../../include/InputHandler.hpp"
#include <algorithm>
#include <iostream>

static rcn3d::Engine& ng = rcn3d::Engine::getInstance();
static rcn3d::InputHandler& inputHandler = rcn3d::InputHandler::getInstance();

void init_engine() {
    rcn3d::SDL_Settings set;
    set.windowSize = glm::vec2(600, 600);
    set.windowPos  = glm::vec2(-1, -1); // SDL_CENTER jeœli -1 jest w tym wektorze
    ng.context_SDL.initContext(set);
}

int main(int argc, char ** argv) {
    init_engine();
    SDL_ShowCursor(1);
    while(true) {
        rcn3d::Event ev;
        while(inputHandler.pollEvent(&ev)){
            if(ev.type == SDL_KEYDOWN) {
                std::cout << "key down: " << (char)ev.getChar() << "\n";
                if(ev.getChar() == 'q'){
                    exit(0);
                }
            }
            if(ev.type == SDL_KEYUP) {
                std::cout << "key up: " << (char)ev.getChar() << "\n";
            }
            if(ev.type == SDL_KEYUP && ev.getChar() == 'i'){
                std::cout << inputHandler.getMouseX() << " " << inputHandler.getMouseY() << ", "
                << inputHandler.getMouseDesktopX() << " " << inputHandler.getMouseDesktopY() << "\n";
            }
            if(inputHandler.isMouseButtonDown(SDL_BUTTON_LEFT)) {
               std::cout << "left button down!\n";
            }
        }
        glClearColor(0.25f, 0.0f, 0.0f, 0.0f);
        ng.context_SDL.swapBuffers();
    }
}



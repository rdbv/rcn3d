#include "../include/InputHandler.hpp"

using namespace rcn3d;

int InputHandler::keyboardSize;
const Uint8* InputHandler::keyboardSDL_state;
std::vector<KeyState> InputHandler::keyboard;

InputHandler::InputHandler() {
    initHandler();
}

void InputHandler::pollEvents() {
    SDL_Event ev;

    while(SDL_PollEvent(&ev)) {
   
        switch(ev.type) {
            case SDL_KEYDOWN:
                handleKeyDown(ev);
                break;
            case SDL_KEYUP:
                handleKeyUp(ev);
                break;
        }

    }
}

KeyState InputHandler::getKeyState(int k) {
    return keyboard[k];
}

void InputHandler::initHandler() {
    keyboardSDL_state = SDL_GetKeyboardState(&keyboardSize);  
    keyboard.resize(keyboardSize);
    std::for_each(keyboard.begin(), keyboard.end(), [](KeyState& k) { k = KeyReleased; });    
}

void InputHandler::handleKeyDown(SDL_Event& ev) {
    char c = ev.key.keysym.sym;
    bool rep = ev.key.repeat;
  
    if(rep) {
        keyboard[c] = KeyRepeated;
        return;
    }
    
    if(keyboard[c] == KeyReleased) {
        keyboard[c] = KeyPressed;
    }
}

void InputHandler::handleKeyUp(SDL_Event& ev) {
    char c = ev.key.keysym.sym;
    keyboard[c] = KeyReleased;
}

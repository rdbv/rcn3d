#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include "../include/SDL_Context.hpp"
#include <string>
#include <vector>
#include <algorithm>

namespace rcn3d {

enum KeyState { 
    KeyPressed, KeyReleased, KeyRepeated 
};

auto getStateString = [](KeyState s) {
    switch(s) {
        case KeyPressed:
            return "KeyPressed";
        case KeyReleased:
            return "KeyReleased";
        case KeyRepeated:
            return "KeyRepeated";
    }
    return "???";
};

class InputHandler 
{
public:

    static InputHandler& getInstance() {
        static InputHandler handler;
        return handler;
    }

    static void pollEvents();

    static KeyState getKeyState(int);

private:
    InputHandler();

    static void initHandler();
    
    static void handleKeyDown(SDL_Event&);
    static void handleKeyUp(SDL_Event&);

    static int keyboardSize;
    static const Uint8* keyboardSDL_state;
    static std::vector<KeyState> keyboard;    
};

} // namespace rcn3d

#endif

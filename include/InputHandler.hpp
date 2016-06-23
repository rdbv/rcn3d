#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include "../include/SDL_Context.hpp"
#include "../include/Event.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <map>

namespace rcn3d {

class InputHandler
{
public:

    static InputHandler& getInstance() {
        static InputHandler handler;
        return handler;
    }

    static bool pollEvent(Event*);
    static bool isKeyDown(int c);
    static bool isMouseButtonDown(int b);
    static double getMouseX();
    static double getMouseY();
    static double getMouseDesktopX();
    static double getMouseDesktopY();

private:
    InputHandler(){};

    static std::map<int, bool> keyboardEventsProxy;
    static std::map<int, bool> mouseEventsProxy;

};

} // namespace rcn3d

#endif

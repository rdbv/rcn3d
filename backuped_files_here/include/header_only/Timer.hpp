#ifndef RCN3D_TIMER_HPP
#define RCN3D_TIMER_HPP

#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL/SDL.h>
#else
#endif

namespace rcn3d {

class Timer {
public:

    void start() {
        startTicks = SDL_GetTicks();
    }

    Uint32 stop() {
        stopTicks = SDL_GetTicks();
        Uint32 delta = stopTicks - startTicks;
        return delta;
    }

private:

    Uint32 startTicks;
    Uint32 stopTicks;
};

}

#endif //RCN3D_TIMER_HPP

#ifndef RCN3D_TIMER_HPP
#define RCN3D_TIMER_HPP

#include <SDL/SDL.h>

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

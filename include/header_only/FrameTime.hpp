#ifndef RCN3D_FRAMETIME_HPP
#define RCN3D_FRAMETIME_HPP

#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL/SDL.h>
#else
#endif

#include <array>
#include <algorithm>
#include <iostream>

namespace rcn3d {

class FrameTime {
public:
    FrameTime() {
        frameTimes.fill(16);
    }
    ~FrameTime() {}

    void begin() {
        startTicks = SDL_GetTicks();
    }

    void end() {
        float frameTicks = SDL_GetTicks() - startTicks;
        if(frameTicks < 1000.0f / 60.0f) {
            SDL_Delay(static_cast<Uint32>((1000.0f / 60.0f) - frameTicks));
        }
        calculateFps();
    }

    Uint32 getRawDelta() {
        return delta;
    }

    float getDeltaTime() {
        return delta / 1000.0f;
    }

private:
    void calculateFps() {
        delta = SDL_GetTicks() - startTicks;
        frameTimes[currentFrame % numberOfSamples] = delta;
        currentFrame++;

        float avg = (std::accumulate(frameTimes.begin(), frameTimes.end(), 0.0f)) / (numberOfSamples);
        static int c = 0;
        if(avg > 0 && c > 60) {
            //std::cout << 1000.0f / avg << "\n";
            c = 0;
        }
        c++;
    }

    Uint32  startTicks;
    Uint32  delta;

    int     currentFrame = 0;
    static const int   numberOfSamples = 10;
    std::array <Uint32, numberOfSamples> frameTimes;
};

}

#endif //RCN3D_FRAMETIME_HPP

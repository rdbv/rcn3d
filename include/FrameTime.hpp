#ifndef RCN3D_FRAMETIME_HPP
#define RCN3D_FRAMETIME_HPP

#include <SDL/SDL.h>
#include <array>
#include <algorithm>
#include <iostream>

namespace rcn3d {

class FrameTime {
public:
    FrameTime() {
        m_frameTimes.fill(16.0f);
    }
    ~FrameTime() {}

    void begin() {
        m_startTicks = SDL_GetTicks();
    }

    void end() {
        float frameTicks = SDL_GetTicks() - m_startTicks;
        if(frameTicks < 1000.0f / 60.0f) {
            SDL_Delay(static_cast<Uint32>((1000.0f / 60.0f) - frameTicks));
        }
        calculateFps();
    }

    float getDeltaTime() {
        return m_delta / 1000.0f;
    }

private:
    void calculateFps() {
        m_delta = SDL_GetTicks() - m_startTicks;
        m_frameTimes[m_currentFrame % m_numberOfSamples] = m_delta;
        m_currentFrame++;

        float avg = (std::accumulate(m_frameTimes.begin(), m_frameTimes.end(), 0.0f)) / (m_numberOfSamples);
        static int c = 0;
        if(avg > 0 && c > 60) {
            std::cout << 1000.0f / avg << "\n";
            c = 0;
        }
        c++;
    }

    Uint32  m_startTicks;
    Uint32  m_delta;

    int     m_currentFrame = 0;
    static const int   m_numberOfSamples = 10;
    std::array <Uint32, m_numberOfSamples> m_frameTimes;
};

}

#endif //RCN3D_FRAMETIME_HPP

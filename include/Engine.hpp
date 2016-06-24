#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "../include/header_only/Math.hpp"
#include "../include/header_only/DebugCamera.hpp"
#include "../include/header_only/GPUData.hpp"

#include "../include/SDL_Context.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/VertexArray.hpp"
#include "../include/VertexBuffer.hpp"
#include "../include/FrameTime.hpp"

namespace rcn3d {

class Engine
{
public:

    static Engine& getInstance() {
        static Engine ng;
        return ng;
    }

    SDL_Context context_SDL;

private:
    Engine() {}
    Engine(const Engine&)   = delete;
    void operator=(Engine&) = delete;
};

} // namespace rcn3d

#endif

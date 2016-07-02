#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "../include/header_only/Math.hpp"
#include "../include/header_only/VertexArray.hpp"
#include "../include/header_only/VertexBuffer.hpp"
#include "../include/header_only/DebugCamera.hpp"
#include "../include/header_only/FrameTime.hpp"
#include "../include/header_only/Texture.hpp"
#include "../include/header_only/Timer.hpp"

#include "../include/SDL_Context.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/TextureLoader.hpp"
#include "../include/Renderer.hpp"

namespace rcn3d {

class Engine
{
public:

    static Engine& getInstance() {
        static Engine ng;
        return ng;
    }

    SDL_Context           context_SDL;
    static TextureLoader& txl;
    static Renderer&      ren;

private:

    Engine() {}
    Engine(const Engine&)   = delete;
    void operator=(Engine&) = delete;
};


} // namespace rcn3d

#endif

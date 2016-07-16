#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "header_only/Math.hpp"
#include "header_only/VertexArray.hpp"
#include "header_only/VertexBuffer.hpp"
#include "header_only/Camera.hpp"
#include "header_only/FrameTime.hpp"
#include "header_only/Texture.hpp"
#include "header_only/Timer.hpp"
#include "header_only/ObjLoader.hpp"

#include "SDL_Context.hpp"
#include "ShaderProgram.hpp"
#include "TextureLoader.hpp"
#include "Renderer.hpp"
#include "Transform.hpp"

namespace rcn3d {

class Engine
{
public:

    static Engine& getInstance() {
        static Engine ng;
        return ng;
    }

    static SDL_Context           context_SDL;
    static TextureLoader& txl;
    static Renderer&      ren;

private:

    Engine() {}
    Engine(const Engine&)   = delete;
    void operator=(Engine&) = delete;
};


} // namespace rcn3d

#endif

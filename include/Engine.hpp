#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "../include/header_only/Math.hpp"
#include "../include/header_only/DebugCamera.hpp"
#include "../include/SDL_Context.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/VertexArray.hpp"
#include "../include/VertexBuffer.hpp"

namespace rcn3d {

class Engine
{
public:

    Engine() {
    }

    SDL_Context context_SDL;

private:
    
};

} // namespace rcn3d

#endif

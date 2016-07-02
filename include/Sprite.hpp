#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "header_only/Texture.hpp"
#include "header_only/GameObject.hpp"
#include "Renderer.hpp"

namespace rcn3d {

class Sprite: public GameObject
{
public:
    Sprite();
    Sprite(Texture*);
    void setTexture(Texture*);

    void draw(Renderer*, glm::mat4 proj, glm::mat4 view);

private:
    Texture* texture;
    glm::vec4 color;
};

}
#endif // SPRITE_HPP

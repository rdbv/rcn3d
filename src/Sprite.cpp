#include "Sprite.hpp"

using namespace rcn3d;

Sprite::Sprite() {}
Sprite::Sprite(Texture* t) {
    setTexture(t);
    color = glm::vec4(1.0, 0.5, 0.5, 1.0);
}

void Sprite::setTexture(Texture* t) {
    texture = t;
}

void Sprite::draw(Renderer* r, glm::mat4 mProjection, glm::mat4 mView) {
    r->spriteShader.run();
    r->spriteShader.setUniform("mvp",mProjection*mView*getGlobalTransformMatrix());
    r->spriteShader.setUniform("tex0",0);
    r->spriteShader.setUniform("r",color.x);
    r->spriteShader.setUniform("g",color.y);
    r->spriteShader.setUniform("b",color.z);
    r->spriteShader.setUniform("a",color.w);

    r->spriteVAO.bind(0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    r->spriteVAO.unbind();
}


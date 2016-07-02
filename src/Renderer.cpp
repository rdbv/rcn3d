#include "../include/Renderer.hpp"

using namespace rcn3d;

VertexArray Renderer::spriteVAO;
ShaderProgram Renderer::spriteShader;

void Renderer::enableWireframe(bool en) {
    if(en)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::getSpriteVAO() {
    float spriteVertices[] = {
        1,  -1,  0,  1,  0,
       -1,  -1,  0,  0,  0,
       -1,   1,  0,  0,  1,
       -1,   1,  0,  0,  1,
        1,   1,  0,  1,  1,
        1,  -1,  0,  1,  0
    };
    VertexBuffer vbo;
    spriteVAO.createVertexArrays(1);
    vbo.createVertexBuffers(2);
    spriteVAO.bind(0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    vbo.bind(GL_ARRAY_BUFFER, 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(spriteVertices), spriteVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (GLvoid*)0);

    vbo.bind(GL_ARRAY_BUFFER, 1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(spriteVertices), spriteVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (GLvoid*)(3 * sizeof(float)));

    spriteVAO.unbind();
    spriteVAO.addVertexBuffer(0, vbo);
}



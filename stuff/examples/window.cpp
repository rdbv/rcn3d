#include "../../include/Engine.hpp"

GLfloat vx[] = {
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};

int main( int argc, char *argv[] ) {

    rcn3d::Engine e;
    rcn3d::SDL_Settings set;
    set.windowPos = glm::vec2(1900, 0);
    e.context_SDL.initContext(set);

    rcn3d::ShaderProgram s0("stuff/shaders/test0.vs",
                            "stuff/shaders/test0.fs");
    glViewport(0, 0, set.windowSize.x, set.windowSize.y);

    GLuint VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vx), vx, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);


    while(true) {
        SDL_Event ev;

        while(SDL_PollEvent(&ev)) {
            if(ev.type == SDL_KEYDOWN) {
                if(ev.key.keysym.sym == 'q')
                    exit(0);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.25f, 0.0f, 0.0f, 0.0f);

        s0.run();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        e.context_SDL.swapBuffers();
    }


}


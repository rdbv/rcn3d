#include "../../include/Engine.hpp"

static rcn3d::Engine& ng = rcn3d::Engine::getInstance();
static rcn3d::DebugCamera cam;

static glm::mat4 proj, view, mvp;

void init_engine() {
    rcn3d::SDL_Settings set;

    set.windowSize = glm::vec2(800, 800);
    set.windowPos  = glm::vec2(-1, -1); // SDL_CENTER jeśli -1 jest w tym wektorze

    proj = glm::perspective(glm::radians(45.0f), set.windowSize.x / set.windowSize.y, 0.1f, 100.0f);

    ng.context_SDL.initContext(set);
}

rcn3d::VertexArray get_triangle() {

    std::vector<glm::vec3> vx_data{
       {0.5f, -0.5f, 0.0f},
       {-0.5f, -0.5f, 0.0f},
       {0.0f,  0.5f, 0.0f}
    };
    
    rcn3d::VertexArray  vao;
    rcn3d::VertexBuffer vbo(1);

    vbo.createVertexBuffers();
    vao.createVertexArrays();

    vao.bind();
    vbo.bind(GL_ARRAY_BUFFER, 0);

    glBufferData(GL_ARRAY_BUFFER, vx_data.size() * sizeof(glm::vec3), &vx_data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    vao.unbind();
    return vao;
}

// Trójkąt, się powinien pokazać.
int main() {
    init_engine();

    rcn3d::ShaderProgram s0("stuff/shaders/test0.vs", 
                            "stuff/shaders/test0.fs");

    s0.addUniform("mvp");
    // można też dodawać 
    // auto uni_map = s0.addUniforms({"mvp", "pvp", "xD"});

    rcn3d::VertexArray vao_triangle = get_triangle();
    glm::mat4 model_triangle = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    while(true) {
        SDL_Event ev;
        while(SDL_PollEvent(&ev)) {
            if(ev.type == SDL_KEYDOWN) {
                exit(0);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.25f, 0.0f, 0.0f, 0.0f);

        view = cam.getViewMatrix();
        mvp = proj * view * model_triangle;

        s0.run();
        s0.setUniform("mvp", mvp);

        vao_triangle.bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
        vao_triangle.unbind();

        ng.context_SDL.swapBuffers();
    }

}


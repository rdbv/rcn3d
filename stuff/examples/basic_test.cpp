#include "../../include/Engine.hpp"
#include <map>
#include <algorithm>
#include <functional>

/*
 * Do stestowania czy działa
 */

static rcn3d::Engine& ng = rcn3d::Engine::getInstance();
static rcn3d::DebugCamera cam;

static glm::mat4 proj, view, mvp;
static std::map<Uint32, bool> keys;

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
    rcn3d::VertexBuffer vbo;

    vbo.createVertexBuffers(1);
    vao.createVertexArrays(1);

    vao.bind(0);
    vbo.bind(GL_ARRAY_BUFFER, 0);

    glBufferData(GL_ARRAY_BUFFER, vx_data.size() * sizeof(glm::vec3), &vx_data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    vao.unbind();
    return vao;
}

rcn3d::VertexArray get_func_col(const std::function<float(float)>& fy,
                                const std::function<float(float)>& fc,
                                std::size_t vx_count = 256, float x_start = 0.0f) {

    std::vector<glm::vec3> vx_data, cl_data;
    float x = x_start, c = 0.25f;
    for(std::size_t i=0;i<vx_count;++i) {
        glm::vec3 vx, cl;

        vx.x = x, vx.y = fy(x);

        cl.b = 0.5f;
        cl.g = fc(c);

        vx_data.push_back(vx);
        cl_data.push_back(cl);

        x += 0.1f, c += 0.1f;
    }

    rcn3d::VertexArray vao;
    rcn3d::VertexBuffer vbo;

    vao.createVertexArrays(1);
    vbo.createVertexBuffers(2);

    
    vao.bind(0);
    vbo.bind(GL_ARRAY_BUFFER, 0);

    glBufferData(GL_ARRAY_BUFFER, vx_data.size() * sizeof(glm::vec3), &vx_data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    vbo.bind(GL_ARRAY_BUFFER, 1);
    glBufferData(GL_ARRAY_BUFFER, cl_data.size() * sizeof(glm::vec3), &cl_data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    glEnableVertexAttribArray(1);

    vao.unbind();

    return vao;
}

#include "../cube_vx.hpp"

rcn3d::VertexArray get_cube() {
    rcn3d::VertexArray vao;
    rcn3d::VertexBuffer vbo;

    vao.createVertexArrays(1);
    vbo.createVertexBuffers(2);

    vao.bind(0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    vbo.bind(GL_ARRAY_BUFFER, 0);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0);
   
    vbo.bind(GL_ARRAY_BUFFER, 1);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    
    vao.unbind();

    vao.addVertexBuffer(0, 0, vbo);
    return vao;
}

// Trójkąt, się powinien pokazać.
// i wykresy.
int main(int argc, char ** argv) {
    init_engine();
    SDL_SetRelativeMouseMode(SDL_TRUE);

    // Shaders
    rcn3d::ShaderProgram s0("../stuff/shaders/test0.vs",
                            "../stuff/shaders/test0.fs");

    rcn3d::ShaderProgram s1("../stuff/shaders/test1_color.vs",
                            "../stuff/shaders/test1_color.fs");

    s0.addUniform("mvp");
    s1.addUniform("mvp");

    // można też dodawać
    // auto uni_map = s0.addUniforms({"mvp", "pvp", "xD"});

    // 'Modele'
    rcn3d::VertexArray vao_triangle = get_triangle();
    glm::mat4 model_triangle = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    // Funkcja liniowa
    rcn3d::VertexArray vao_linear = get_func_col([](float y){ return 2*y; },
                                                 [](float c){ return c; });
    glm::mat4 model_linear = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // Funkcja kwadratowa
    rcn3d::VertexArray vao_quadratic = get_func_col([](float y) { return y*y; },
                                                    [](float c) { return 0.25f; }, 256, -8.0f);
    glm::mat4 model_quadratic = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, 0.0f));

    // Kostka
    rcn3d::VertexArray vao_cube = get_cube();
    glm::mat4 model_cube = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f));

    rcn3d::FrameTime frameTime;

    while(true) {
        frameTime.begin();

        SDL_Event ev;
        while(SDL_PollEvent(&ev)) {
            if(ev.type == SDL_KEYDOWN) {
                keys[ev.key.keysym.sym] = true;
            }
            else if(ev.type == SDL_KEYUP) {
                keys[ev.key.keysym.sym] = false;
            }
            else if(ev.type == SDL_MOUSEMOTION) {
                float x = ev.motion.xrel, y = ev.motion.yrel;
                cam.processMouse(x, -y);
            }
        }

        if(keys['q'])exit(0);
        if(keys['w']) cam.processKeyboard(rcn3d::FORWARD, frameTime.getDeltaTime());
        if(keys['s']) cam.processKeyboard(rcn3d::BACKWARD, frameTime.getDeltaTime());
        if(keys['a']) cam.processKeyboard(rcn3d::LEFT, frameTime.getDeltaTime());
        if(keys['d']) cam.processKeyboard(rcn3d::RIGHT, frameTime.getDeltaTime());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.25f, 0.0f, 0.0f, 0.0f);

        view = cam.getViewMatrix();
        mvp = proj * view * model_cube;

        s0.run();
        s0.setUniform("mvp", mvp);

        vao_cube.bind(0);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        vao_cube.unbind();

        mvp = proj * view * model_triangle;
        s0.setUniform("mvp", mvp);

        vao_triangle.bind(0);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        vao_triangle.unbind();



        mvp = proj * view * model_linear;
        s1.run();
        s1.setUniform("mvp", mvp);

        vao_linear.bind(0);
            glDrawArrays(GL_LINES, 0, 256);
        vao_linear.unbind();

        mvp = proj * view * model_quadratic;
        s1.setUniform("mvp", mvp);

        vao_quadratic.bind(0);
            glDrawArrays(GL_LINES, 0, 256);
        vao_quadratic.unbind();


        ng.context_SDL.swapBuffers();
        frameTime.end();
    }

}


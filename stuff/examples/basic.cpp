#include <cstdio>
#include <map>

#include "../../include/header_only/Math.hpp"
#include "../../include/header_only/Camera.hpp"
#include "../../include/header_only/FrameTime.hpp"
#include "../../include/header_only/Window.hpp"
#include "../../include/header_only/Shader.hpp"

using namespace rcn3d;

static Window win;
static DebugCamera cam;
static FrameTime ft;
static ShaderProgram sprog0;

static std::map<Uint32, bool> keys;
static glm::mat4 p, v;

void init() {
    win.init_sdl();
    win.init_gl();

    if(sprog0.load_shader("stuff/shaders/gles_300/test0.vs",
                          "stuff/shaders/gles_300/test0.fs") == false)
        exit(0);

    sprog0.add_uniform("mvp", true);

    auto i_s = win.get_init_size();
    p = glm::perspective(glm::radians(45.0f), i_s.x/i_s.y, 0.1f, 100.0f);
}


GLuint get_triangle() {
    std::vector<glm::vec3> vx_data {
        { -0.5, 0.0, 0.0 },
        {  0.0, 0.5, 0.0 },
        {  0.5, 0.0, 0.0 },
    };

    std::vector<glm::vec3> cl_data {
        { 1.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 1.0 }
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, vx_data.size()*sizeof(glm::vec3), &vx_data[0],  GL_STATIC_DRAW);

    return vbo;
}

int main() {
    init();

    float t = 0;

    auto triangle = get_triangle();
    glm::mat4 triangle_m = glm::translate(glm::mat4(1), glm::vec3(0));

    while(process_events(keys, cam, ft, t)) {
        ft.begin();

        v = cam.get_view_matrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.30, 0.0, 0.0, 0);

        sprog0.run();
        sprog0.set_uniform("mvp", p*v*triangle_m);
        
        glBindBuffer(GL_ARRAY_BUFFER, triangle);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        ft.end();
        SDL_GL_SwapWindow(win.get_win_handle());
    }
}


#include "../../include/header_only/Window.hpp"
#include "../../include/header_only/Shader.hpp"
#include "../../include/header_only/Camera.hpp"
#include "../../include/header_only/FrameTime.hpp"

static Window win;
static ShaderProgram s_prog0;
static KeyMap keys;
static FrameTime ft;
static DebugCamera cam;
static glm::mat4 p, v;

void init_engine() {
    win.init_sdl();
    win.init_gl();
    auto is = win.get_init_size();
    p = glm::perspective(glm::radians(45.0f), is.x/is.y, 0.1f, 100.0f);
}

void load_shaders() {
    if(!s_prog0.load_shader("stuff/shaders/gles_300/test0.vs",
                            "stuff/shaders/gles_300/test0.fs"))
        exit(0);

    s_prog0.add_uniform("mvp", true);

}


GLuint get_triangle() {
    std::vector<glm::vec3> vx_data {
        { -0.5, 0.0, 0.0 },
        {  0.0, 0.5, 0.0 },
        {  0.5, 0.0, 0.0 },
    };
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vx_data.size()*sizeof(glm::vec3), &vx_data[0], GL_STATIC_DRAW);
    return vbo;
}

int main() {
    init_engine();
    load_shaders();

    GLuint tr0_vbo = get_triangle();
    glm::mat4 tr0_mx = glm::translate(glm::mat4(1), glm::vec3(0));

    while(process_events(keys, cam, ft)) {
        ft.begin();

        v = cam.get_view_matrix();

        glClearColor(0.30, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       
        s_prog0.run();
        s_prog0.set_uniform("mvp", p*v*tr0_mx);

        glBindBuffer(GL_ARRAY_BUFFER, tr0_vbo);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        ft.end();

        SDL_GL_SwapWindow(win.get_win_handle());
    }

}


#include <cstdio>
#include <map>

#include "../../include/SDL_Context.hpp"
#include "../../include/ShaderProgram.hpp"
#include "../../include/header_only/Math.hpp"
#include "../../include/header_only/Camera.hpp"
#include "../../include/header_only/FrameTime.hpp"

using namespace rcn3d;

static SDL_Context ctx;
static glm::mat4 p, v, m;
static DebugCamera cam;
static FrameTime ft;
static std::map<Uint32, bool> keys;

void init_engine(glm::vec2 window_size = glm::vec2(800, 800), 
                 glm::vec2 window_pos  = glm::vec2(1950, 0) ) {
    SDL_Settings set;
    set.windowSize = window_size, set.windowPos = window_pos;
    p = glm::perspective(glm::radians(45.0f), set.windowSize.x/set.windowSize.y, 0.1f, 100.0f);
    
    /* SLD_SetRelativeMouseMode(SDL_TRUE) */
    SDL_SetRelativeMouseMode(SDL_TRUE);

    ctx.initContext(set);
}

bool process_events() {
    SDL_Event ev;

    while(SDL_PollEvent(&ev)) {
        if(ev.type == SDL_KEYDOWN) keys[ev.key.keysym.sym] = true;
        if(ev.type == SDL_KEYUP)   keys[ev.key.keysym.sym] = false;
        if(ev.type == SDL_MOUSEMOTION) {
            float x = ev.motion.xrel, y = -ev.motion.yrel;
            cam.process_mouse(x, y);
        }
    }
    
    if(keys['q']) return false;

    if(keys['w']) cam.process_keyboard(FORWARD, ft.getDeltaTime());
    if(keys['s']) cam.process_keyboard(BACKWARD, ft.getDeltaTime());
    if(keys['a']) cam.process_keyboard(LEFT, ft.getDeltaTime());
    if(keys['d']) cam.process_keyboard(RIGHT, ft.getDeltaTime());

    return true;
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
    init_engine();

    ShaderProgram s0("stuff/shaders/test0.vs", "stuff/shaders/test0.fs");
    s0.addUniform("mvp");

    GLuint tri = get_triangle();
    glm::mat4 mat_tri0 = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));

    while(process_events()) {
        ft.begin();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.30, 0, 0, 0);

        v = cam.get_view_matrix();

        s0.run();
        
        m = p * v * mat_tri0;
        s0.setUniform("mvp", m);

        glBindBuffer(GL_ARRAY_BUFFER, tri);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        ctx.swapBuffers();

        ft.end();

    }

}



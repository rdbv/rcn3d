#include "../include/Engine.hpp"
#include <functional>

rcn3d::VertexArray get_wave() {
    std::vector<glm::vec3> vx_data;
    const std::size_t vx_count = 256;
    float x = 0.0f;

    for(std::size_t i=0;i<vx_count;++i) {
        glm::vec3 vx(x, 2*x, 0.0f);

        x += 0.1f;

        vx_data.push_back(vx);
    }

    rcn3d::VertexArray vao;
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

rcn3d::VertexArray get_func(const std::function<float(float)>& fy, std::size_t vx_count, float x_step = 0.1f) {
    std::vector<glm::vec3> vx_data;
    float x = 0.0f;
    for(std::size_t i=0;i<vx_count;++i) {
        glm::vec3 vx;

        vx.x = x;
        vx.y = fy(x);
        vx.z = 0.0f;

        vx_data.push_back(vx);
        x += x_step;
    }

    rcn3d::VertexArray vao;
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

rcn3d::VertexArray get_func_col(const std::function<float(float)>& fy,
                                const std::function<float(float)>& fc,
                                std::size_t vx_count = 256, float x_step = 0.1f, float c_step = 0.1f) {
    std::vector<glm::vec3> vx_data, cl_data;
    float x = 0.0f, c = 0.0f;
    for(std::size_t i=0;i<vx_count;++i) {
        glm::vec3 vx, cl;
        vx.x = x, vx.y = fy(x);
        cl.b = 0.5f;
        cl.g = fc(c);
        vx_data.push_back(vx);
        cl_data.push_back(cl);
        x += x_step, c += c_step;
    }

    rcn3d::VertexArray vao(2);
    rcn3d::VertexBuffer vbo(4);

    vao.createVertexArrays();
    vbo.createVertexBuffers();

    vao.bind();
    vbo.bind(GL_ARRAY_BUFFER, 0);

    glBufferData(GL_ARRAY_BUFFER, vx_data.size() * sizeof(glm::vec3), &vx_data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    vbo.bind(GL_ARRAY_BUFFER, 1);
    glBufferData(GL_ARRAY_BUFFER, cl_data.size() * sizeof(glm::vec3), &cl_data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    glEnableVertexAttribArray(1);

    vao.unbind();

    // ==

    for(std::size_t i=0;i<vx_count/2;++i) {
        cl_data[i].g = 0.5f;
    }

    vao.bind(1);
    vbo.bind(GL_ARRAY_BUFFER, 2);

    glBufferData(GL_ARRAY_BUFFER, vx_data.size() * sizeof(glm::vec3), &vx_data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    vbo.bind(GL_ARRAY_BUFFER, 3);
    glBufferData(GL_ARRAY_BUFFER, cl_data.size() * sizeof(glm::vec3), &cl_data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    vao.unbind();

    return vao;
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


int main(int argc, char**argv) {

    bool keys[256*8] {0};

    rcn3d::Engine& ng = rcn3d::Engine::getInstance();
    rcn3d::SDL_Settings set;

    set.windowSize = glm::vec2(1280, 950);
    set.windowPos  = glm::vec2(1900, 0);

    ng.context_SDL.initContext(set);


    rcn3d::ShaderProgram s0("stuff/shaders/test0.vs",
                            "stuff/shaders/test0.fs");

    rcn3d::ShaderProgram s1("stuff/shaders/test1_color.vs",
                            "stuff/shaders/test1_color.fs");

    rcn3d::DebugCamera cam;

    glm::mat4 mvp;
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), set.windowSize.x / set.windowSize.y, 0.1f, 100.0f);
    glm::mat4 view;

    glm::mat4 mod0 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 mod1 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 mod2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mod3 = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
    glm::mat4 mod4 = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f));

    s0.addUniform("mvp");
    s1.addUniform("mvp");

    rcn3d::VertexArray vao = get_wave();
    rcn3d::VertexArray vao0 = get_triangle();
    rcn3d::VertexArray vao1 = get_func([](float x){ return sin(x) * cos(x*2) * sin(x/2); }, 256, 0.1);
    rcn3d::VertexArray vao2 = get_func_col([](float x){ return 2.05*x; }, [](float c){ return sin(c); });

    Uint32 now;
    Uint32 last = 0;
    Uint32 delta = 0;

    GLfloat lastX = set.windowSize.x / 2.0f;
    GLfloat lastY = set.windowSize.y / 2.0f;
    bool firstMouse = true;

    while(true) {

        now = SDL_GetTicks();
        if(now > last) {
            delta = now - last;
            last = now;
        }

        SDL_Event ev;

        while(SDL_PollEvent(&ev)) {
            if(ev.type == SDL_KEYDOWN) {
                if(ev.key.keysym.sym == 'q')
                    exit(0);
                keys[ev.key.keysym.sym] = true;
            }
            else if(ev.type == SDL_KEYUP) {
                keys[ev.key.keysym.sym] = false;
            }
            if(ev.type == SDL_MOUSEMOTION) {
                float x = ev.motion.xrel, y = ev.motion.yrel;
                if(firstMouse) {
                    lastX = x, lastY = y;
                    firstMouse = false;
                }
                float xoff = x - lastX;
                float yoff = lastY - y;
                cam.processMouse(xoff, yoff);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.25f, 0.0f, 0.0f, 0.0f);

        if(keys['w']) cam.processKeyboard(rcn3d::FORWARD, delta);
        if(keys['s']) cam.processKeyboard(rcn3d::BACKWARD, delta);
        if(keys['a']) cam.processKeyboard(rcn3d::LEFT, delta);
        if(keys['d']) cam.processKeyboard(rcn3d::RIGHT, delta);

        // MAX MODELS

        view = cam.getViewMatrix();
        mvp = proj * view * mod0;

        s0.run();
        s0.setUniform("mvp", mvp);

        vao0.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vao0.unbind();

        mvp = proj * view * mod1;
        s0.setUniform("mvp", mvp);

        vao.bind();
        glDrawArrays(GL_LINES, 0, 256);
        vao.unbind();

        mvp = proj * view * mod2;
        s0.setUniform("mvp", mvp);

        vao1.bind();
        glDrawArrays(GL_LINE_STRIP, 0, 256);
        vao1.unbind();

        s1.run();
        mvp = proj * view * mod3;
        s1.setUniform("mvp", mvp);

        vao2.bind();
        glDrawArrays(GL_LINES, 0, 256);
        vao2.unbind();

        mvp = proj * view * mod4;
        s1.setUniform("mvp", mvp);

        vao2.bind(1);
        glDrawArrays(GL_LINES, 0, 256);
        vao2.unbind();

        ng.context_SDL.swapBuffers();
    }


}


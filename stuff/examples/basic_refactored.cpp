#include "../../include/Engine.hpp"
#include <map>

// SET THIS CORRECT !!!!
#define WINDOW_SIZE glm::vec2(800, 800)
#define WINDOW_POS  glm::vec2(2100, 0)

static rcn3d::Engine &ng = rcn3d::Engine::getInstance();
static rcn3d::TextureLoader __attribute__((unused)) &txl = ng.tex_loader;

static rcn3d::DebugCamera cam;
static rcn3d::FrameTime ft;

static glm::mat4 proj, view, mvp;


void init_engine(glm::vec2 windowSize, glm::vec2 windowPos) {
    rcn3d::SDL_Settings st;
    st.windowSize = windowSize;
    st.windowPos = windowPos;
    proj = glm::perspective(glm::radians(45.0f), st.windowSize.x/st.windowSize.y, 0.1f, 100.0f);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    ng.context_SDL.initContext(st);
}

void processEvents(std::map<Uint32, bool>& ks) {
    SDL_Event ev;
    while(SDL_PollEvent(&ev)) {
        if(ev.type == SDL_KEYDOWN) ks[ev.key.keysym.sym] = true;
        if(ev.type == SDL_KEYUP)   ks[ev.key.keysym.sym] = false;
        if(ev.type == SDL_MOUSEMOTION) {
            float x = ev.motion.xrel, y = -ev.motion.yrel;
            cam.processMouse(x, y);
        }
    }
}

void camMovement(std::map<Uint32, bool>& ks) {
    if(ks['w']) cam.processKeyboard(rcn3d::FORWARD, ft.getDeltaTime());
    if(ks['s']) cam.processKeyboard(rcn3d::BACKWARD, ft.getDeltaTime());
    if(ks['a']) cam.processKeyboard(rcn3d::LEFT, ft.getDeltaTime());
    if(ks['d']) cam.processKeyboard(rcn3d::RIGHT, ft.getDeltaTime());
}

/* === MODEL GENERATING === */

template<typename T> std::size_t siz(const std::vector<T>& t) { return t.size() * sizeof(T); }

rcn3d::VertexArray get_triangle_ebo() {
    std::vector<glm::vec3> vx_data {
       {  0.5f, -0.5f, 0.0f },
       { -0.5f, -0.5f, 0.0f },
       {  0.0f,  0.5f, 0.0f }
    };

    std::vector<glm::vec3> vx_color {
        { 0.0f, 0.50f, 0.0f },
        { 0.50f, 0.0f, 0.0f },
        { 0.60f, 0.13f, 0.50f }
    };

    std::vector<unsigned int> vx_ebo {
        0, 1, 2,
    };

    std::vector<unsigned int> color_ebo {
        0, 1, 2,
    };

    rcn3d::VertexArray vao;
    rcn3d::VertexBuffer vbo;

    // create OpenGL objects
    vao.createVertexArrays(1);
    vbo.createVertexBuffers(4);  

    vao.bind(0);

    // enable vertex array in shader
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
  
    // === Vertex
    vbo.bind(GL_ARRAY_BUFFER, 0);
    // set data
    glBufferData(GL_ARRAY_BUFFER, siz(vx_data), &vx_data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);

    // === Colors
    vbo.bind(GL_ARRAY_BUFFER, 1);
    glBufferData(GL_ARRAY_BUFFER, siz(vx_color), &vx_color[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);

    // === EBO vertex
    vbo.bind(GL_ARRAY_BUFFER, 0);
    vbo.bind(GL_ELEMENT_ARRAY_BUFFER, 2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * vx_ebo.size(),
            &vx_ebo[0], GL_STATIC_DRAW);

    // === EBO color
    vbo.bind(GL_ARRAY_BUFFER, 1);
    vbo.bind(GL_ELEMENT_ARRAY_BUFFER, 3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * vx_ebo.size(),
            &color_ebo[0], GL_STATIC_DRAW);


    vao.unbind();

    return vao;
}

int main(int argc, char** argv) {
    init_engine(WINDOW_SIZE, WINDOW_POS);

    std::map<Uint32, bool> keys;

    rcn3d::ShaderProgram s_col("stuff/shaders/test1_color.vs",
                               "stuff/shaders/test1_color.fs");

//    rcn3d::Texture tex_face = txl.loadNormalTexture("stuff/textures/awesomeface.png");

    /* Add uniforms */
    s_col.addUniform("mvp");

    /* Create models */
    rcn3d::VertexArray m_triangle0 = get_triangle_ebo();
    glm::mat4 mx_triangle0 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

    /* Enable wireframe */
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(true) {
        ft.begin();

        processEvents(keys);
        camMovement(keys);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.25f, 0.0f, 0.0f, 0.0f);

        if(keys['q']) break;
        
        view = cam.getViewMatrix();

        s_col.run();
        mvp = proj * view * mx_triangle0;
        s_col.setUniform("mvp", mvp);

        m_triangle0.bind(0);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)0);
        m_triangle0.unbind();

        // === End of render 

        ng.context_SDL.swapBuffers();
        ft.end();
    }


}


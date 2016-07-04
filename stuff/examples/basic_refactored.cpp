#include "../../include/Engine.hpp"

#define WINDOW_SIZE glm::vec2(1200, 800)
#define WINDOW_POS  glm::vec2(2100, 0)

static rcn3d::Engine        &ng  = rcn3d::Engine::getInstance();
static rcn3d::Renderer      &rn  = ng.ren;
static rcn3d::TextureLoader &txl = ng.txl;

static rcn3d::Camera cam;
static rcn3d::FrameTime ft;

static glm::mat4 proj, view, mvp;

void init_engine(glm::vec2 windowSize, glm::vec2 windowPos) {
    rcn3d::SDL_Settings st;
    st.windowSize = windowSize;
    st.windowPos = windowPos;
    proj = glm::perspective(glm::radians(45.0f), st.windowSize.x/st.windowSize.y, 0.1f, 100.0f);

    rn.setProjMatrix(glm::perspective(glm::radians(45.0f), st.windowSize.x/st.windowSize.y, 0.1f, 100.0f));

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


rcn3d::VertexArray get_triangle() {
    std::vector<glm::vec3> vx_data {
        { -0.5, 0.0, 0.0 },
        {  0.0, 0.5, 0.0 },
        {  0.5, 0.0, 0.0 },
    };
    
    std::vector<glm::vec3> cl_data {
        { 1.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 1.0 },
    };

    rcn3d::VertexArray  vao;
    rcn3d::VertexBuffer vbo;

    // Create buffer
    vao.createVertexArrays(1); 
    vbo.createVertexBuffers(2);

    // Bind VAO[0] 
    vao.bind(0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    vbo.bind(GL_ARRAY_BUFFER, 0);
    vbo.bufferData_gl(&vx_data[0], siz(vx_data));
    vbo.vxAttribPtr_gl(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    vbo.setUsage(RCN_VX);

    vbo.bind(GL_ARRAY_BUFFER, 1);
    vbo.bufferData_gl(&cl_data[0], siz(cl_data));
    vbo.vxAttribPtr_gl(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
    vbo.setUsage(RCN_COLOR);

    vao.unbind();
    vao.addVertexBuffer(0, vbo);

    return vao;
}

int main(int argc, char** argv) {
    std::map<Uint32, bool> keys;
    init_engine(glm::vec2(900, 900),
                glm::vec2(-1, -1));

    rcn3d::ShaderProgram s_col("stuff/shaders/test1_color.vs",
                               "stuff/shaders/test1_color.fs");

    s_col.addUniform("mvp");

    rcn3d::VertexArray vao_triangle0 = get_triangle();
    
    rcn3d::Renderable* ren0 = rn.createRenderable("r0");
    ren0->setVertexArray(&vao_triangle0); ren0->setShader(&s_col);
    ren0->setPosition(0.0f, 0.0f, -2.0f);

    rcn3d::Renderable* ren1 = rn.createRenderable("r1");
    ren1->setVertexArray(&vao_triangle0); ren1->setShader(&s_col);
    ren1->setParent(ren0);
    ren1->translate(-2.0f, 0.0f, 0.0f);

    rcn3d::Renderable* ren2 = rn.createRenderable("r2");
    ren2->setVertexArray(&vao_triangle0); ren2->setShader(&s_col);
    ren2->setParent(ren0);
    ren2->translate(2.0f, 0.0f, 0.0f);

    while(true) {
        ft.begin();
        processEvents(keys); camMovement(keys);

        if(keys['q']) break;
        if(keys['e']) ren0->rotateX(0.6666 *  ft.getDeltaTime());
        if(keys['r']) ren0->rotateX(0.6666 * -ft.getDeltaTime());

        rn.setViewMatrix(cam.getViewMatrix());

        rn.clearScreen(glm::vec4(0.30, 0.0f, 0.0f, 0.0f));
        
        rn.renderAll();

        ng.context_SDL.swapBuffers();
        ft.end();
    }

}

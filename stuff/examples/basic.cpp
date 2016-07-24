
#include "../../include/Chunk.hpp"
#include "../../include/TextureLoader.hpp"
#include "../../include/PerlinsMap.hpp"

#include "../../include/header_only/Window.hpp"
#include "../../include/header_only/Shader.hpp"
#include "../../include/header_only/Camera.hpp"
#include "../../include/header_only/FrameTime.hpp"

static Window win;

static ShaderProgram s_prog0, s_prog_chunk_dbg, s_prog_chunk_tex;

static Texture tex_mc0;

static KeyMap keys;
static FrameTime ft;
static DebugCamera cam;
static TextureLoader tex_loader;

static glm::mat4 p, v;

static rcn3d::PerlinsMap perlinsMap;

void init_engine() {
    win.init_sdl();
    win.init_gl();
    auto is = win.get_init_size();
    p = glm::perspective(glm::radians(45.0f), is.x/is.y, 0.1f, 100.0f);
    tex_mc0 = tex_loader.loadNormalTexture("stuff/textures/textures.png");
}

void load_shaders() {
    if(!s_prog0.load_shader("stuff/shaders/gles_300/test0.vs",
                            "stuff/shaders/gles_300/test0.fs"))
        exit(0);

    if(!s_prog_chunk_dbg.load_shader("stuff/shaders/gles_300/test0_chunk_debug.vs",
                                     "stuff/shaders/gles_300/test0_chunk_debug.fs"))
        exit(0);

    if(!s_prog_chunk_tex.load_shader("stuff/shaders/gles_300/test0_chunk.vs",
                                     "stuff/shaders/gles_300/test0_chunk.fs"))
        exit(0);

    s_prog0.add_uniform("mvp", true);
    s_prog_chunk_dbg.add_uniform("mvp", true);

    s_prog_chunk_tex.add_uniform("mvp", true);
    s_prog_chunk_tex.add_uniform("tex_mc", true);
}

void init_map() {
    perlinsMap.generateMap(10, 10, 10.0f, 8, 0.5f, 2.0f);
}

int main(int argc, char** argv) {
    init_engine();
    load_shaders();
    init_map();

	std::vector <Chunk> realMap;
	for(auto& i : perlinsMap.getMapData()) {
		realMap.emplace_back();
		realMap.back().init_chunk(i.x * 0.25f, i.y * 0.25f, i.z * 0.25f);
		realMap.back().generate();
	}
//
//    Chunk c0;
//    glm::mat4 ch0_mx = glm::translate(glm::mat4(1), glm::vec3(0));
//
//    c0.init_chunk(); c0.generate();
//
//    Chunk c1;
//    glm::mat4 ch1_mx = glm::translate(glm::mat4(1), glm::vec3(4.25, 0.0, 0.0));
//
//    c1.init_chunk(); c1.generate();
//
//    Chunk c2;
//    glm::mat4 ch2_mx = glm::translate(glm::mat4(1), glm::vec3(8.50, 0.0, 0.0));
//
//    c2.init_chunk(); c2.generate();

    while(process_events(keys, cam, ft)) {
        ft.begin();

        v = cam.get_view_matrix();

        glClearColor(0.30, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		s_prog_chunk_tex.run();
		for(int i = 0; i < realMap.size(); i++) {
			s_prog_chunk_tex.set_uniform("mvp", p * v * realMap[i].getMatrix());
			realMap[i].render();
		}

//        // Draw 1 chunq
//        s_prog_chunk_dbg.run();
//        s_prog_chunk_dbg.set_uniform("mvp", p*v*ch0_mx);
//
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        c0.render();
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//        // Draw 2 chunq
//        s_prog_chunk_tex.run();
//        s_prog_chunk_tex.set_uniform("mvp", p*v*ch1_mx);
//
//        c1.render();
//
//        // Draw 3 chunq
//        s_prog_chunk_tex.set_uniform("mvp", p*v*ch2_mx);
//
//        c2.render();

        ft.end();

        SDL_GL_SwapWindow(win.get_win_handle());
    }

}


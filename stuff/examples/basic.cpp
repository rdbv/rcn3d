
#include "../../include/Chunk.hpp"
#include "../../include/TextureLoader.hpp"
#include "../../include/PerlinsMap.hpp"

#include "../../include/header_only/Window.hpp"
#include "../../include/header_only/Shader.hpp"
#include "../../include/header_only/Camera.hpp"
#include "../../include/header_only/FrameTime.hpp"
#include "../../include/header_only/BitmapFont.hpp"

static Window win;

static ShaderProgram s_prog0, s_prog_chunk_dbg, s_prog_chunk_tex, s_bitmap_font;

static Texture tex_mc0;

static KeyMap           keys;
static FrameTime        ft;
static DebugCamera      cam;
static TextureLoader    tex_loader;
static PerlinsMap       perlinMap;

static glm::mat4 p, v;

void init_engine() {
    win.init_sdl();
    win.init_gl();
    auto is = win.get_init_size();
    p = glm::perspective(glm::radians(45.0f), is.x/is.y, 0.1f, 100.0f);
    tex_mc0 = tex_loader.loadNormalTexture("stuff/textures/textures.png");
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void load_shaders() {
    if(!s_prog0.load_shader("stuff/shaders/gles_300_to_330/test0.vs",
                            "stuff/shaders/gles_300_to_330/test0.fs"))
        exit(0);

    if(!s_prog_chunk_dbg.load_shader("stuff/shaders/gles_300_to_330/test0_chunk_debug.vs",
                                     "stuff/shaders/gles_300_to_330/test0_chunk_debug.fs"))
        exit(0);

    if(!s_prog_chunk_tex.load_shader("stuff/shaders/gles_300_to_330/test0_chunk.vs",
                                     "stuff/shaders/gles_300_to_330/test0_chunk.fs"))
        exit(0);
    if(!s_bitmap_font.load_shader("stuff/shaders/font0.vs",
                                  "stuff/shaders/font0.fs"))
        exit(0);

    s_prog0.add_uniform("mvp", true);
    s_prog_chunk_dbg.add_uniform("mvp", true);

    s_prog_chunk_tex.add_uniform("mvp", true);
    s_prog_chunk_tex.add_uniform("tex_mc", true);
}

int main(int argc, char** argv) {
    init_engine();
    load_shaders();

    rcn3d::BitmapFont bmf1;
    bmf1.load("stuff/fonts/CalibriBitmap2.fnt", &tex_loader, &s_bitmap_font, win.get_win_handle());

    perlinMap.generateMap(10, 10, 2.0f, 8, 0.5f, 2.0f);
    const std::vector <glm::ivec3> mapData = perlinMap.getMapData();

    /* wspolrzedne sa ok */
    Chunk c0;
    c0.init_chunk(0, 0, 0);
//    Chunk c1;
//    c1.init_chunk(8, 0, 0);
//    Chunk c2;
//    c2.init_chunk(16, 0, 0);

    for(const auto& i : mapData) {
        c0.set_block_type(i.x % CX, i.y % CY, i.z % CZ, BLOCK_DIRT);
    }
//    for(int z=0;z<CZ;++z) {
//        for(int x=0;x<CX;++x) {
//            c0.set_block_type(x, 0, z, BLOCK_DIRT);
//        }
//    }

//    for(int z=0;z<CZ;++z) {
//        for(int x=0;x<CX;++x) {
//            c1.set_block_type(x, 0, z, BLOCK_TREE_UP);
//        }
//    }
//
//    for(int z=0;z<CZ;++z) {
//        for(int x=0;x<CX;++x) {
//            c2.set_block_type(x, 0, z, BLOCK_BRICKS);
//        }
//    }

//    // Dziura w ceglach po srodku
//    c2.set_block_type(CX/2, 0, CZ/2, BLOCK_AIR);
//    // Latajace drewno, tutaj jest poczatek chunka
//    //
//    c1.set_block_type(0, 4, 0, BLOCK_TREE_UP);
//
//    // Generuj z macierzy
    c0.generate();
//    c1.generate();
//    c2.generate();

    while(process_events(keys, cam, ft)) {
        ft.begin();

        v = cam.get_view_matrix();

        glClearColor(0.30, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw chunq
        s_prog_chunk_tex.run();
        tex_mc0.bind(GL_TEXTURE_2D);
        s_prog_chunk_dbg.set_uniform("mvp", p*v*c0.getMatrix());

        c0.render();

//        s_prog_chunk_tex.set_uniform("mvp", p*v*c1.getMatrix());

//        c1.render();
//
//        s_prog_chunk_tex.set_uniform("mvp", p*v*c2.getMatrix());
//        c2.render();

        bmf1.drawString("Your SPECIAL SECRET KEY:\n"
                        "https://www.youtube.com/watch?v=dQw4w9WgXcQ", 42, 420);
        ft.end();
        SDL_GL_SwapWindow(win.get_win_handle());
    }
    return 0;
}


#include "gui/gui.h"

#include "imgui.h"
#include "examples/imgui_impl_sdl.h"
#include "examples/imgui_impl_opengl3.h"
#include "SDL.h"

#include <cassert>
#include <iostream>

// TODO: Handle quit.

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

Gui::Gui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    if (SDL_Init(SDL_INIT_VIDEO)) {
        const char * error = SDL_GetError();
        std::cout << "Error in SDL_Init: " << error << std::endl;
        assert(false);
    }
    auto window = SDL_CreateWindow(
        "ELPtracer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH * 2,
        SCREEN_HEIGHT * 2,
        0
    );

    auto context = SDL_GL_CreateContext(window);

    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init();

}
void Gui::Show() const {
  while(true) {
    // TODO: Event loop.
  }
  Cleanup();
}

void Gui::Cleanup() const {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
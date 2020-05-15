#include "gui/gui.h"

#include "imgui.h"
#include "examples/imgui_impl_sdl.h"
#include "examples/imgui_impl_opengl3.h"

#include "gui/camera_window.h"
#include "gui/lights_window.h"
#include "gui/objects_window.h"
#include "gui/preview_window.h"

#include "display/png_writer.h"
#include "scene/camera.h"
#include "scene/world.h"

#include <cassert>
#include <iostream>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>            // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h>  // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>// Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

Gui::Gui() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    if (SDL_Init(SDL_INIT_VIDEO)) {
        const char * error = SDL_GetError();
        std::cout << "Error in SDL_Init: " << error << std::endl;
        assert(false);
    }

    window_ = SDL_CreateWindow(
        "ELPtracer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH * 2,
        SCREEN_HEIGHT * 2,
        (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)
    );

    context_ = SDL_GL_CreateContext(window_);
    SDL_GL_MakeCurrent(window_, context_);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window_, context_);
    ImGui_ImplOpenGL3_Init();

    preview_canvas_ = new Canvas(300, 300);
    preview_window_ = new PreviewWindow(preview_canvas_);
    camera_window_ = new CameraWindow(preview_canvas_);
    lights_window_ = new LightsWindow();
    objects_window_ = new ObjectsWindow();
}

void Gui::Show() {
  while(EventLoop()) {}
  Cleanup();
}

bool Gui::EventLoop() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
        return false;
    }
    ImGui_ImplSDL2_ProcessEvent(&event);
  }

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window_);
  ImGui::NewFrame();

  Frame();

  ImGui::Render();
  // TODO get from actual window size in case it gets resized (io).
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  ImVec4 clear_color = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(window_);

  return true;
}

void Gui::Frame() {
  bool updated = false;
  updated |= camera_window_->Frame();
  updated |= lights_window_->Frame();
  updated |= preview_window_->Frame();
  updated |= objects_window_->Frame();

  if (updated) {
    Update();
  }
}

void Gui::Update() {
  if (camera_) {
    camera_->Cancel();
    free(camera_);
  }
  camera_ = camera_window_->GetCamera();

  world_ = GetWorld();
  std::cout << "Rendering." << std::endl;
  auto canvas = camera_->Render(*world_);
  png_writer_ = new PNGWriter(canvas);
  png_writer_->WriteFile("gui.png");
}

void Gui::Cleanup() const {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

World *Gui::GetWorld() {
  auto world = new World();
  world->set_light(lights_window_->GetPointLight());

  std::vector<Shape *> objects = objects_window_->GetObjects();
  for (auto o : objects) {
    world->add_object(o);
  }

  return world;
}

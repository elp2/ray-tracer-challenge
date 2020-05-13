#include "gui/preview_window.h"

#include "imgui.h"
#include <cstdlib>

#include "display/canvas.h"


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

PreviewWindow::PreviewWindow(Canvas *canvas) {
  canvas_ = canvas;
}

bool PreviewWindow::Frame() {
  ImGui::Begin("Preview");

  ImGui::ProgressBar(Progress(), ImVec2(0.0f, 0.0f));

  if (texture_id_) {
    glDeleteTextures(1, &texture_id_);
  }
  glGenTextures(1, &texture_id_);
  glBindTexture(GL_TEXTURE_2D, texture_id_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, canvas_->width(), canvas_->height(), 0, GL_RGB, GL_FLOAT, canvas_->data());
  glGenerateMipmap(GL_TEXTURE_2D);

  ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
  ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
  ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
  ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
  ImGui::Image((void *)texture_id_, ImVec2(canvas_->width(), canvas_->height()), uv_min, uv_max, tint_col, border_col);


  if (ImGui::Button("Preview")) {

  }

  ImGui::End();

  return false;
}

float PreviewWindow::Progress() const {
  return canvas_->Progress();
}

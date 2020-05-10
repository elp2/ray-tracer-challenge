#include "gui/preview_window.h"

#include "imgui.h"

PreviewWindow::PreviewWindow() {
}

bool PreviewWindow::Frame() {
  ImGui::Begin("Preview");

  ImGui::ProgressBar(Progress(), ImVec2(0.0f, 0.0f));

  if (ImGui::Button("Preview")) {

  }
  
  ImGui::End();

  return false;
}

float PreviewWindow::Progress() const {
  return 0.45;
}

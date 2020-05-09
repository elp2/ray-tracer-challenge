#include "preview_window.h"

#include "imgui.h"

PreviewWindow::PreviewWindow() {
}

void PreviewWindow::Frame() {
  ImGui::Begin("Preview");

  ImGui::ProgressBar(Progress(), ImVec2(0.0f, 0.0f));

  if (ImGui::Button("Preview")) {

  }
  
  ImGui::End();
}

const float PreviewWindow::Progress() const {
  return 0.45;
}

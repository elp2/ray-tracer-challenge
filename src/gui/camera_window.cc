#include "camera_window.h"

#include <iostream>
#include "imgui.h"

CameraWindow::CameraWindow() {
}

void CameraWindow::Frame() {
  ImGui::Begin("Camera");

  bool updated = false;

  ImGui::Text("Position"); ImGui::SameLine();
  ImGui::PushItemWidth(50);
  updated |= ImGui::InputFloat("X", &x_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("Y", &y_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("Z", &z_, 0, 0, "%.3f");
  ImGui::PopItemWidth();

  ImGui::Text("Facing"); ImGui::SameLine();
  ImGui::PushItemWidth(50);
  updated |= ImGui::InputFloat("X1", &facing_x_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("Y1", &facing_y_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("Z1", &facing_z_, 0, 0, "%.3f");
  ImGui::PopItemWidth();

  ImGui::Text("Up"); ImGui::SameLine();
  ImGui::PushItemWidth(50);
  updated |= ImGui::InputFloat("X2", &up_x_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("Y2", &up_y_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("Z2", &up_z_, 0, 0, "%.3f");
  ImGui::PopItemWidth();

  if (updated) {
    std::cout << "Updated: " << x_ << ", " << y_ << ", " << z_ << std::endl;
  }

  ImGui::End();
}

#include "gui/camera_window.h"

#include <iostream>
#include "imgui.h"
#include <math.h>

#include "scene/camera.h"

CameraWindow::CameraWindow() {
}

bool CameraWindow::Frame() {
  ImGui::Begin("Camera");

  bool updated = false;

  ImGui::Text("Position"); ImGui::SameLine();
  ImGui::PushItemWidth(50);
  updated |= ImGui::InputFloat("X", &x_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("Y", &y_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("Z", &z_, 0, 0, "%.3f");
  ImGui::PopItemWidth();

  ImGui::Text("Facing Point"); ImGui::SameLine();
  ImGui::PushItemWidth(50);
  updated |= ImGui::InputFloat("FX", &facing_x_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("FY", &facing_y_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("FZ", &facing_z_, 0, 0, "%.3f");
  ImGui::PopItemWidth();

  ImGui::Text("Up Vector"); ImGui::SameLine();
  ImGui::PushItemWidth(50);
  updated |= ImGui::InputFloat("UX", &up_x_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("UY", &up_y_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("UZ", &up_z_, 0, 0, "%.3f");
  ImGui::PopItemWidth();

  ImGui::Text("Field of View"); ImGui::SameLine();
  ImGui::PushItemWidth(100);
  updated |= ImGui::SliderFloat("Radians", &field_of_view_, 0.0f, M_PI, "%.4f", 2.0f);
  ImGui::PopItemWidth();

  // TODO: Add aperature radius, focal length, rays per pixel behind a checkbox.

  ImGui::End();

  return updated;
}

Camera *CameraWindow::GetCamera() {
  const int WIDTH = 50;
  const int HEIGHT = 50;
  return new Camera(WIDTH, HEIGHT, field_of_view_, aperature_radius_, focal_length_, rays_per_pixel_);
}
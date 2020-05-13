#include "gui/lights_window.h"

#include "imgui.h"

#include "primitives/tuple.h"

LightsWindow::LightsWindow() {
}

bool LightsWindow::Frame() {
  ImGui::Begin("Lights");

  bool updated = false;

  ImGui::Text("Position");
  updated |= ImGui::SliderFloat("X", &x_, -10, 10, "%.2f", 2.0f);
  updated |= ImGui::SliderFloat("Y", &y_, -10, 10, "%.2f", 2.0f);
  updated |= ImGui::SliderFloat("Z", &z_, -10, 10, "%.2f", 2.0f);
  updated |= ImGui::ColorEdit3("Color", color_);

  ImGui::End();
  return updated;
}

PointLight LightsWindow::GetPointLight() {
  Tuple position = Point(x_, y_, z_);
  Color color = Color(color_[0], color_[1], color_[2]);
  return PointLight(position, color);
}

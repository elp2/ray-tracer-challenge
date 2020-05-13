#include "gui/camera_window.h"

#include <iostream>
#include "imgui.h"
#include <math.h>

#include "display/canvas.h"
#include "primitives/tuple.h"
#include "scene/camera.h"
#include "scene/view_transformation.h"

CameraWindow::CameraWindow(Canvas *canvas) {
  canvas_ = canvas;
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

  ImGui::Text("To"); ImGui::SameLine();
  ImGui::PushItemWidth(50);
  updated |= ImGui::InputFloat("FX", &to_x_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("FY", &to_y_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("FZ", &to_z_, 0, 0, "%.3f");
  ImGui::PopItemWidth();

  ImGui::Text("Up Vector"); ImGui::SameLine();
  ImGui::PushItemWidth(50);
  updated |= ImGui::InputFloat("UX", &up_x_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("UY", &up_y_, 0, 0, "%.3f"); ImGui::SameLine();
  updated |= ImGui::InputFloat("UZ", &up_z_, 0, 0, "%.3f");
  ImGui::PopItemWidth();

  ImGui::Text("Field of View"); ImGui::SameLine();
  ImGui::PushItemWidth(100);
  updated |= ImGui::SliderFloat("Radians", &field_of_view_, 0.1f, M_PI - 0.1f, "%.4f", 2.0f);
  ImGui::PopItemWidth();

  // TODO: Add aperature radius, focal length, rays per pixel behind a checkbox.

  ImGui::End();

  return updated;
}

Camera *CameraWindow::GetCamera() {
  auto camera = new Camera(canvas_->width(), canvas_->height(), field_of_view_);
  Tuple from = Point(x_, y_, z_);
  Tuple to = Point(to_x_, to_y_, to_z_);
  Tuple up = Vector(up_x_, up_y_, up_z_);
  camera->set_transform(ViewTransformation(from, to, up));
  camera->set_canvas(canvas_);
  return camera;
}

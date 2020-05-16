#include "gui/objects_window.h"

#include "imgui.h"

#include "gui/object_view.h"
#include "shapes/sphere.h"

ObjectsWindow::ObjectsWindow() {
  object_view_ = new ObjectView();
}

bool ObjectsWindow::Frame() {
  ImGui::Begin("Objects");

  bool updated = object_view_->Frame();

  ImGui::End();

  return updated;
}

std::vector<Shape *> ObjectsWindow::GetObjects() {
  std::vector<Shape *>objects;

  auto shape = object_view_->GetShape();
  if (nullptr == shape) {
    return objects;
  }

  objects.push_back(shape);

  return objects;
}

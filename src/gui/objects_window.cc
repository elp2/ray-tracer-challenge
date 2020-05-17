#include "gui/objects_window.h"

#include "imgui.h"

#include "gui/item_list.h"
#include "gui/object_view.h"
#include "shapes/sphere.h"

ObjectsWindow::ObjectsWindow() {
  list_ = new ItemList();
}

bool ObjectsWindow::Frame() {
  ImGui::Begin("Objects");

  bool updated = list_->Frame();

  ImGui::End();

  return updated;
}

std::vector<Shape *> ObjectsWindow::GetObjects() {
  return list_->Items();
}

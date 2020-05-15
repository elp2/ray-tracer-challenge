#include "gui/objects_window.h"

#include "shapes/sphere.h"

#include "imgui.h"

ObjectsWindow::ObjectsWindow() {
}

bool ObjectsWindow::Frame() {
  ImGui::Begin("Objects");

  bool updated = false;

  ImGui::End();

  return updated;
}

std::vector<Shape *> ObjectsWindow::GetObjects() {
  std::vector<Shape *>objects;

  auto sphere = new Sphere();
  auto material = Material();
  material.set_color(Color(0.6, 0.6, 0.6));
  sphere->set_material(material);
  objects.push_back(sphere);

  return objects;
}

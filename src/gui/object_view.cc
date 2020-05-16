#include "gui/object_view.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include "imgui.h"

#include "shapes/cone.h"
#include "shapes/cube.h"
#include "shapes/cylinder.h"
#include "shapes/group.h"
#include "shapes/obj_parser.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"

ObjectView::ObjectView() {
}

bool ObjectView::Frame() {
  const char *types[] = { "Cone", "Cube", "Cylinder", "Plane", "Sphere", "Teapot", "Unknown" };
  const char *type_label = types[type_];
  if (ImGui::BeginCombo("Type", type_label, 0)) {
      for (int n = 0; n < IM_ARRAYSIZE(types); n++) {
          const bool is_selected = (type_ == n);
          if (ImGui::Selectable(types[n], is_selected)) {
              type_ = (ObjectType)n;
          }

          // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
          if (is_selected) {
            ImGui::SetItemDefaultFocus();
          }
      }
      ImGui::EndCombo();
  }

  return false;
}

Shape *ObjectView::GetShape() {
  Shape *object;
  switch (type_) {
    case ObjectType_Cone:
      object = GetCone();
      break;
    case ObjectType_Cube:
      object = GetCube();
      break;
    case ObjectType_Cylinder:
      object = GetCylinder();
      break;
    case ObjectType_Plane:
      object = GetPlane();
      break;
    case ObjectType_Sphere:
      object = GetSphere();
      break;
    case ObjectType_Teapot:
      object = GetTeapot();
      break;
    case ObjectType_Unknown:
      return nullptr;
    default:
      assert(false);
      break;
  }

  return object;
}

Cone *ObjectView::GetCone() {
  return new Cone(maximum_, minimum_, closed_);
}

Cube *ObjectView::GetCube() {
  return new Cube();
}

Cylinder *ObjectView::GetCylinder() {
  return new Cylinder(maximum_, minimum_, closed_);
}

Plane *ObjectView::GetPlane() {
  return new Plane();
}

Sphere *ObjectView::GetSphere() {
  return new Sphere();
}

Group *ObjectView::GetTeapot() {
  std::ifstream model("teapot-low.obj");
  assert(model.is_open());
  std::stringstream ss;
  ss << model.rdbuf();
  model.close();

  auto parser = ObjParser(ss);
  return parser.GroupNamed("Teapot001")->OptimizedSubgroups(5);
}

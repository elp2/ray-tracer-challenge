#include "gui/material_view.h"

#include "imgui.h"

MaterialView::MaterialView() {
}

bool MaterialView::Frame() {
  bool updated = false;

  updated |= ImGui::ColorEdit3("Color", color_);
  updated |= ImGui::SliderFloat("Ambient", &ambient_, 0.0, 1.0, "%.4f", 2.0f);
  updated |= ImGui::SliderFloat("Diffuse", &diffuse_, 0.0, 1.0, "%.4f", 2.0f);
  updated |= ImGui::SliderFloat("Specular", &specular_, 0.0, 1.0, "%.4f", 2.0f);
  updated |= ImGui::SliderFloat("Shininess", &shininess_, 10.0, 200.0, "%.4f", 2.0f);
  updated |= ImGui::SliderFloat("Reflective", &reflective_, 0.0, 1.0, "%.4f", 2.0f);
  updated |= ImGui::SliderFloat("Refractive Index", &refractive_index_, REFRACTIVE_INDEX_VACUUM, REFRACTIVE_INDEX_DIAMOND, "%.4f", 2.0f);
  updated |= ImGui::SliderFloat("Transparency", &transparency_, 0.0, 1.0, "%.4f", 2.0f);

  return updated;
}

Material MaterialView::GetMaterial() {
  Material material = Material();
  material.set_ambient(ambient_);
  material.set_diffuse(diffuse_);
  material.set_specular(specular_);
  material.set_shininess(shininess_);
  material.set_reflective(reflective_);
  material.set_refractive_index(refractive_index_);
  material.set_transparency(transparency_);
  Color color = Color(color_[0], color_[1], color_[2]);
  material.set_color(color);

  return material;
}

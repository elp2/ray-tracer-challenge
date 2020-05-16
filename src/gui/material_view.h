#ifndef RTC_GUI_MATERIAL_VIEW_H
#define RTC_GUI_MATERIAL_VIEW_H

#include <math.h>

#include "shapes/material.h"

class MaterialView {
 public:
  MaterialView();
  ~MaterialView() = default;

  // Returns whether the widgets changed this frame.
  bool Frame();

  // Returns the material.
  Material GetMaterial();

 private:
  float ambient_ = MATERIAL_DEFAULT_AMBIENT;
  float diffuse_ = MATERIAL_DEFAULT_DIFFUSE;
  float reflective_ = MATERIAL_DEFAULT_REFLECTIVE;
  float refractive_index_ = MATERIAL_DEFAULT_REFRACTIVE_INDEX;
  float specular_ = MATERIAL_DEFAULT_SPECULAR;
  float shininess_ = MATERIAL_DEFAULT_SHININESS;
  float transparency_ = MATERIAL_DEFAULT_TRANSPARENCY;
};

#endif    // RTC_GUI_MATERIAL_VIEW_H

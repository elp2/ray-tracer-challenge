#include "primitives/color.h"

#include "shapes/material.h"

Material::Material() {
  color_ = Color(1.0, 1.0, 1.0);
  ambient_ = 0.1;
  diffuse_ = 0.9;
  specular_ = 0.9;
  shininess_ = 200.0;
}

bool Material::operator==(Material other) const {
  return other.color() == color_ && other.ambient() == ambient_ && 
    other.diffuse() == diffuse_ && other.specular() == specular_ &&
    other.shininess() == shininess_;
}

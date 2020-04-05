#include "primitives/color.h"

#include "shapes/material.h"

#include <math.h>

Material::Material() {
  color_ = Color(1.0, 1.0, 1.0);
  ambient_ = 0.1;
  diffuse_ = 0.9;
  reflective_ = 0.0;
  specular_ = 0.9;
  shininess_ = 200.0;
}

bool Material::operator==(Material other) const {
  return other.color() == color_ && other.ambient() == ambient_ && 
    other.diffuse() == diffuse_ && other.specular() == specular_ &&
    other.shininess() == shininess_;
}

Color Material::Lighting(PointLight light, Tuple position, Tuple eye_vector,
  Tuple normal_vector, bool in_shadow) {
  Color point_color = pattern_ == nullptr ? color_ : pattern_->ColorAt(position);
  Color effective_color = point_color * light.intensity();
  Tuple light_vector = (light.position() - position).Normalized();
  Color ambient_color = effective_color * ambient_;
  if (in_shadow) {
    return ambient_color;
  }

  float light_dot_normal = light_vector.Dot(normal_vector);
  Color diffuse_color;
  Color specular_color;
  if (light_dot_normal < 0.0) {
    // Light on other side of surface. No Diffuse or Specular contribution.
    diffuse_color = Color(0.0, 0.0, 0.0);
    specular_color = Color(0.0, 0.0, 0.0);
  } else {
    diffuse_color = effective_color * (diffuse_ * light_dot_normal);

    Tuple reflection_vector = (-light_vector).Reflect(normal_vector);
    float reflection_dot_eye = reflection_vector.Dot(eye_vector);
    if (reflection_dot_eye <= 0.0) {
      // Light reflects away from eye. No specular contribution.
      specular_color = Color(0.0, 0.0, 0.0);
    } else {
      float factor = pow(reflection_dot_eye, shininess_);
      specular_color = light.intensity() * (specular_ * factor);
    }
  }

  return ambient_color + diffuse_color + specular_color;
}

#include "primitives/color.h"

#include "shapes/material.h"
#include "shapes/shape.h"

#include <math.h>

Material::Material() {
  color_ = Color(1.0, 1.0, 1.0);
  ambient_ = MATERIAL_DEFAULT_AMBIENT;
  diffuse_ = MATERIAL_DEFAULT_DIFFUSE;
  reflective_ = MATERIAL_DEFAULT_REFLECTIVE;
  refractive_index_ = MATERIAL_DEFAULT_REFRACTIVE_INDEX;
  specular_ = MATERIAL_DEFAULT_SPECULAR;
  shininess_ = MATERIAL_DEFAULT_SHININESS;
  transparency_ = MATERIAL_DEFAULT_TRANSPARENCY;
}

bool Material::operator==(Material other) const {
  return other.color() == color_ && other.ambient() == ambient_ &&
    other.diffuse() == diffuse_ && other.specular() == specular_ &&
    other.shininess() == shininess_;
}

Color Material::Lighting(const PointLight &light, const Tuple &position,
    const Tuple &eye_vector, const Tuple &normal_vector, float shadowing, const Shape *shape) const {
  Tuple color_point = shape == nullptr ? position : shape->WorldPointToObject(position);
  Color point_color = pattern_ == nullptr ? color_ : pattern_->ColorAt(color_point);
  Color effective_color = point_color * light.intensity();
  Tuple light_vector = (light.position() - position).Normalized();
  Color ambient_color = effective_color * ambient_;
  if (shadowing == 1.0) {
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

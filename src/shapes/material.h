#ifndef RTC_SHAPES_MATERIAL_H_
#define RTC_SHAPES_MATERIAL_H_

#include "lights/point_light.h"
#include "patterns/pattern.h"
#include "primitives/color.h"
#include "primitives/tuple.h"

class Material {
 public:
  Material();
  ~Material() = default;

  Color Lighting(PointLight light, Tuple position, Tuple eye_vector, Tuple normal_vector, bool in_shadow);

  Color color() { return color_; };
  void set_color(Color color) { color_ = color; };

  // 0.0 - 1.0.
  float ambient() { return ambient_; };
  void set_ambient(float ambient) { ambient_ = ambient; };  

  // 0.0 - 1.0.
  float diffuse() { return diffuse_; };
  void set_diffuse(float diffuse) { diffuse_ = diffuse; };

  // 0.0 - 1.0.
  float specular() { return specular_; };
  void set_specular(float specular) { specular_ = specular; };

  // 10.0 - 200.0..
  float shininess() { return shininess_; };
  void set_shininess(float shininess) { shininess_ = shininess; };

  // When not set, uses the color.
  void set_pattern(Pattern *pattern) { pattern_ = pattern; };
  Pattern *pattern() const { return pattern_; };

  // 1.0 = mirror, 0.0 = completely unreflective.
  void set_reflective(float reflective) { reflective_ = reflective; };
  float reflective() const { return reflective_; };

  bool operator==(Material other) const;

 private:
  Color color_;
  float ambient_;
  float diffuse_;
  float reflective_;
  float specular_;
  float shininess_;
  Pattern *pattern_ = nullptr;
};

#endif    // RTC_SHAPES_MATERIAL_H_

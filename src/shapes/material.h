#ifndef RTC_SHAPES_MATERIAL_H_
#define RTC_SHAPES_MATERIAL_H_

#include "primitives/color.h"
#include "primitives/tuple.h"

class Material {
 public:
  Material();
  ~Material() = default;

  Color color() { return color_; };
  void set_color(Color color) { color_ = color; };

  float ambient() { return ambient_; };
  void set_ambient(float ambient) { ambient_ = ambient; };  

  float diffuse() { return diffuse_; };
  void set_diffuse(float diffuse) { diffuse_ = diffuse; };

  float specular() { return specular_; };
  void set_specular(float specular) { specular_ = specular; };

  float shininess() { return shininess_; };
  void set_shininess(float shininess) { shininess_ = shininess; };

  bool operator==(Material other) const;

 private:
  Color color_;
  float ambient_;
  float diffuse_;
  float specular_;
  float shininess_;
};

#endif    // RTC_SHAPES_MATERIAL_H_

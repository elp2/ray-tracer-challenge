#ifndef RTC_SHAPES_MATERIAL_H_
#define RTC_SHAPES_MATERIAL_H_

#include "lights/point_light.h"
#include "patterns/pattern.h"
#include "primitives/color.h"
#include "primitives/tuple.h"

static const float REFRACTIVE_INDEX_VACUUM = 1.0;
static const float REFRACTIVE_INDEX_AIR = 1.00029;
static const float REFRACTIVE_INDEX_WATER = 1.333;
static const float REFRACTIVE_INDEX_GLASS = 1.5;
static const float REFRACTIVE_INDEX_DIAMOND = 2.417;

static const float MATERIAL_DEFAULT_AMBIENT = 0.1;
static const float MATERIAL_DEFAULT_DIFFUSE = 0.9;
static const float MATERIAL_DEFAULT_REFLECTIVE = 0.0;
static const float MATERIAL_DEFAULT_REFRACTIVE_INDEX = REFRACTIVE_INDEX_VACUUM;
static const float MATERIAL_DEFAULT_SPECULAR = 0.9;
static const float MATERIAL_DEFAULT_SHININESS = 200.0;
static const float MATERIAL_DEFAULT_TRANSPARENCY = 0.0;

class Shape;

class Material {
 public:
  Material();
  ~Material() = default;

  Color Lighting(const PointLight &light, const Tuple &position,
      const Tuple &eye_vector, const Tuple &normal_vector, float shadowing, const Shape *shape) const;

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

  // 1.0 = vacuum.
  void set_refractive_index(const float refractive_index) { refractive_index_ = refractive_index; };
  float refractive_index() const { return refractive_index_; };

  // 1.0 = transparent, 0.0 = opaque.
  void set_transparency(const float transparency) { transparency_ = transparency; };
  float transparency() const { return transparency_; };

  void set_casts_shadow(const bool casts_shadow) { casts_shadow_ = casts_shadow; };
  bool casts_shadow() const { return casts_shadow_; };

  bool operator==(Material other) const;

 private:
  Color color_;
  float ambient_;
  float diffuse_;
  float reflective_;
  float refractive_index_;
  float specular_;
  float shininess_;
  float transparency_;
  bool casts_shadow_ = true;
  Pattern *pattern_ = nullptr;
};

#endif    // RTC_SHAPES_MATERIAL_H_

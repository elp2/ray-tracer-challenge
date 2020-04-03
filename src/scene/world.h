#ifndef RTC_SCENE_WORLD_H
#define RTC_SCENE_WORLD_H

class Intersections;
class Ray;

#include <vector>

#include "lights/point_light.h"
#include "shapes/sphere.h"
#include "scene/prepared_computation.h"

class World {
 public:
  World();
  ~World() = default;

  Intersections Intersect(Ray r);
  Color ShadeHit(PreparedComputation pc);
  Color ColorAt(Ray r);
  bool IsShadowed(Tuple p);

  std::vector<Sphere> objects() const { return objects_; };
  void add_object(Sphere s) { objects_.push_back(s); };

  PointLight light() const { return light_; };
  void set_light(PointLight light) { light_ = light; };

 private:
  std::vector<Sphere> objects_;
  PointLight light_;
};

World DefaultWorld();

#endif    // RTC_SCENE_WORLD_H

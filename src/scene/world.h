#ifndef RTC_SCENE_WORLD_H
#define RTC_SCENE_WORLD_H

class Intersections;
class Ray;

#include <vector>

#include "lights/point_light.h"
#include "shapes/shape.h"
#include "scene/prepared_computation.h"

class World {
 public:
  World();
  ~World() = default;

  Intersections Intersect(const Ray r);
  Color ShadeHit(PreparedComputation pc);
  Color ColorAt(Ray r);
  bool IsShadowed(Tuple p);
  Color ReflectedColor(PreparedComputation pc);

  std::vector<Shape *> objects() const { return objects_; };
  void add_object(Shape *s) { objects_.push_back(s); };

  PointLight light() const { return light_; };
  void set_light(PointLight light) { light_ = light; };

 private:
  std::vector<Shape *> objects_;
  PointLight light_;
};

World DefaultWorld();

#endif    // RTC_SCENE_WORLD_H

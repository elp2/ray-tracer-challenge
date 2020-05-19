#ifndef RTC_SCENE_WORLD_H
#define RTC_SCENE_WORLD_H

class Intersections;
class Ray;

#include <vector>

#include "lights/point_light.h"
#include "shapes/shape.h"
#include "scene/prepared_computation.h"

static const int MAX_REFLECTIONS = 5;
static const int MAX_REFRACTIONS = 5;

class World {
 public:
  World();
  ~World() = default;

  Intersections Intersect(const Ray r);
  Color ShadeHit(PreparedComputation pc, const int &reflections);
  Color ColorAt(Ray r);
  float Shadowing(Tuple p);
  Color ReflectedColor(PreparedComputation &pc, const int &reflections);
  Color RefractedColor(PreparedComputation &pc, const int &refractions);

  std::vector<Shape *> objects() const { return objects_; };
  void add_object(Shape *s) { objects_.push_back(s); };

  PointLight light() const { return light_; };
  void set_light(PointLight light) { light_ = light; };

 private:
  Color ColorAt(Ray r, const int &reflections);

  std::vector<Shape *> objects_;
  PointLight light_;
};

World DefaultWorld();

#endif    // RTC_SCENE_WORLD_H

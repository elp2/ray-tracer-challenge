#include "scene/world.h"

#include "primitives/transformation.h"
#include "primitives/intersection.h"
#include "primitives/intersections.h"

World::World() {
  light_ = PointLight();
}

Intersections World::Intersect(Ray r) {
  Intersections xs = Intersections(std::vector<Intersection> {});

  for (std::vector<Sphere>::const_iterator i = objects_.begin(); i < objects_.end(); ++i) {
    xs.Merge((*i).Intersect(r));
  }

  return xs;
}

Color World::ShadeHit(PreparedComputation pc) {
  bool is_shadowed = IsShadowed(pc.over_point());

  // TODO: Iterate through all light sources and add colors.
  Sphere *s = (Sphere *)pc.object();
  return s->material().Lighting(light_, pc.point(), pc.eye_vector(), pc.normal_vector(), is_shadowed);
}

Color World::ColorAt(Ray r) {
  Intersections xs = Intersect(r);
  std::optional<Intersection> i = xs.Hit();
  if (!i.has_value()) {
    return Color(0.0, 0.0, 0.0);
  }

  PreparedComputation pc = PreparedComputation(i.value(), r);
  return ShadeHit(pc);
}

World DefaultWorld() {
  World w = World();

  Sphere s1 = Sphere();
  Material m1 = Material();
  m1.set_color(Color(0.8, 1.0, 0.6));
  m1.set_diffuse(0.7);
  m1.set_specular(0.2);
  s1.set_material(m1);
  w.add_object(s1);

  Sphere s2 = Sphere();
  s2.SetTransform(Scaling(0.5, 0.5, 0.5));
  w.add_object(s2);

  PointLight light = PointLight(Point(-10.0, 10.0, -10.0), Color(1.0, 1.0, 1.0));
  w.set_light(light);
  return w;
}

bool World::IsShadowed(Tuple p) {
  Tuple v = light_.position() - p;
  Tuple direction = v.Normalized();
  Ray r = Ray(p, direction);

  Intersections xs = Intersect(r);
  if (!xs.Hit().has_value()) {
    return false;
  }
  Intersection hit = xs.Hit().value();
  float light_distance = v.Magnitude();
  bool first_hit_closer = hit.T() < light_distance;
  return first_hit_closer;
}

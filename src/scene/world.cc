#include "scene/world.h"

#include "primitives/transformation.h"
#include "primitives/intersection.h"
#include "primitives/intersections.h"
#include "shapes/sphere.h"

World::World() {
  light_ = PointLight();
}

Intersections World::Intersect(const Ray r) {
  Intersections xs = Intersections(std::vector<Intersection> {});

  for (std::vector<Shape *>::const_iterator i = objects_.begin(); i < objects_.end(); ++i) {
    xs.Merge((*i)->Intersect(r));
  }

  return xs;
}

Color World::ShadeHit(PreparedComputation pc) {
  bool is_shadowed = IsShadowed(pc.over_point());

  const Shape *s = pc.object();
  Color surface = s->material().Lighting(light_, pc.point(), pc.eye_vector(), pc.normal_vector(), is_shadowed);
  Color reflected = ReflectedColor(pc);
  return surface + reflected;
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

  auto s1 = new Sphere();
  Material m1 = Material();
  m1.set_color(Color(0.8, 1.0, 0.6));
  m1.set_diffuse(0.7);
  m1.set_specular(0.2);
  s1->set_material(m1);
  w.add_object(s1);

  auto s2 = new Sphere();
  s2->SetTransform(Scaling(0.5, 0.5, 0.5));
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

Color World::ReflectedColor(PreparedComputation pc) {
  if (pc.object()->material().reflective() == 0.0) {
    return Color(0, 0, 0);
  }
  Ray reflected_ray = Ray(pc.over_point(), pc.reflect_vector());
  Color reflected_color = ColorAt(reflected_ray);
  return reflected_color * pc.object()->material().reflective();
}

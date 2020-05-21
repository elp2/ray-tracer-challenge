#include "scene/world.h"

#include <math.h>

#include "lights/light.h"
#include "lights/point_light.h"
#include "primitives/transformation.h"
#include "primitives/intersection.h"
#include "primitives/intersections.h"
#include "shapes/sphere.h"

World::World() {
  light_ = new PointLight();
}

Intersections World::Intersect(const Ray r) {
  Intersections xs = Intersections(std::vector<Intersection> {});

  for (std::vector<Shape *>::const_iterator i = objects_.begin(); i < objects_.end(); ++i) {
    xs.Merge((*i)->Intersect(r));
  }

  return xs;
}

Color World::ShadeHit(PreparedComputation pc, const int &reflections) {
  Color surface = Color(0, 0, 0);
  const Shape *s = pc.object();

  auto lightlets = light_->LightletsForPoint(pc.over_point());
  for (auto lightlet : lightlets) {
    float shadowing = lightlet->ShadowingForPoint(pc.over_point());
    if (shadowing != 1.0) {
      shadowing = LightShadowed(pc.over_point(), lightlet->position()) ? 1.0 : shadowing;
    }
    surface = surface + s->Lighting(lightlet, pc.over_point(), pc.eye_vector(), pc.normal_vector(), shadowing);
  }
  surface = surface * (1.0 / (float)lightlets.size());

  Color reflected = ReflectedColor(pc, reflections);
  Color refracted = RefractedColor(pc, reflections);

  Material hit_material = pc.object()->material();
  if (hit_material.reflective() > 0 && hit_material.transparency() > 0) {
    float reflectance = pc.schlick();
    return surface + reflected * reflectance + refracted * (1 - reflectance);
  }

  return surface + reflected + refracted;
}

Color World::ColorAt(Ray r) {
  return ColorAt(r, 0);
}

Color World::ColorAt(Ray r, const int &reflections) {
  Intersections xs = Intersect(r);
  std::optional<Intersection> i = xs.Hit();
  if (!i.has_value()) {
    return Color(0.0, 0.0, 0.0);
  }

  PreparedComputation pc = PreparedComputation(i.value(), r, xs);
  return ShadeHit(pc, reflections);
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

  auto light = new PointLight(Point(-10.0, 10.0, -10.0), Color(1.0, 1.0, 1.0));
  w.set_light(light);
  return w;
}

float World::Shadowing(Tuple p) {
  float shadowing = 0.0;
  auto lightlets = light_->LightletsForPoint(p);
  for (auto lightlet : lightlets) {
    float lightlet_shadowing = lightlet->ShadowingForPoint(p);
    if (lightlet_shadowing == 1.0) {
      // Fully shadowed - no need to also check intersections.
      shadowing += lightlet_shadowing;
      continue;
    }
    shadowing += LightShadowed(p, lightlet->position()) ? 1.0 : lightlet_shadowing;
  }
  return shadowing / (float)lightlets.size();
}

bool World::LightShadowed(const Tuple &p, const Tuple &light_position) {
  Tuple v = light_position - p;
  Tuple direction = v.Normalized();
  Ray r = Ray(p, direction);

  Intersections xs = Intersect(r);
  if (!xs.Hit().has_value()) {
    // Nothing between point and light - no shadow.
    return 0.0;
  }
  Intersection hit = xs.Hit().value();
  Shape *s = (Shape *)xs.Hit()->Object();
  if (!s->material().casts_shadow()) {
    // Material casts no shadow (e.g. water hack) - no shadow.
    return 0.0;
  }

  float light_distance = v.Magnitude();
  bool first_hit_closer = hit.T() < light_distance;
  // If the first intersection is past the light, point is not obstructed.
  return first_hit_closer ? 1.0 : 0.0;
}

Color World::ReflectedColor(PreparedComputation &pc, const int &reflections) {
  if (reflections == MAX_REFLECTIONS) {
    return Color(0, 0, 0);
  }
  if (pc.object()->material().reflective() == 0.0) {
    return Color(0, 0, 0);
  }
  Ray reflected_ray = Ray(pc.over_point(), pc.reflect_vector());
  Color reflected_color = ColorAt(reflected_ray, reflections + 1);
  return reflected_color * pc.object()->material().reflective();
}

Color World::RefractedColor(PreparedComputation &pc, const int &refractions) {
  if (refractions == MAX_REFRACTIONS) {
    return Color(0, 0, 0);
  }
  if (pc.object()->material().transparency() == 0.0) {
    return Color(0, 0, 0);
  }
  float n_ratio = pc.n1() / pc.n2();
  float cos_i = pc.eye_vector().Dot(pc.normal_vector());
  float sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
  if (sin2_t > 1) {
    // Total internal refraction.
    return Color(0, 0, 0);
  }

  float cos_t = sqrt(1.0 - sin2_t);
  Tuple refracted_direction = pc.normal_vector() * (n_ratio * cos_i - cos_t) -
    pc.eye_vector() * n_ratio;
  Ray refracted_ray = Ray(pc.under_point(), refracted_direction);

  return ColorAt(refracted_ray, refractions + 1) * pc.object()->material().transparency();
}

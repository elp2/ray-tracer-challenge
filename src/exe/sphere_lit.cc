#include "display/canvas.h"
#include "display/ppm_writer.h"
#include "lights/point_light.h"
#include "primitives/math.h"
#include "primitives/matrix.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"
#include "shapes/sphere.h"

#include <cassert>
#include <cmath>
#include <iostream>

const float SPHERE_PADDING = 20.0;
const float SPHERE_RADIUS = 100.0;
const int CANVAS_DIMENSION = 2 * SPHERE_PADDING + 2 * SPHERE_RADIUS;
const int INSET = CANVAS_DIMENSION / 2;

void DrawHit(Canvas *canvas, Ray r, Intersection hit, PointLight light) {
  Tuple hit_point = r.Position(hit.T());
  Sphere *s = (Sphere *)hit.Object();
  Tuple normal = s->Normal(hit_point, Intersection(1, &s));
  Tuple eye = -r.Direction();
  auto lightlet = light.LightletsForPoint(hit_point)[0];
  Color color = s->Lighting(lightlet, hit_point, eye, normal, 0.0);

  float x = hit_point.x() + INSET;
  float y = hit_point.y() + INSET;
  canvas->WritePixel(color, x, y);
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  Canvas *canvas = new Canvas(CANVAS_DIMENSION, CANVAS_DIMENSION);

  Sphere s = Sphere();
  Material m = Material();
  m.set_color(Color(1.0, 0.2, 0.2));
  s.set_material(m);

  Color light_color = Color(1.0, 1.0, 1.0);

  PointLight light = PointLight(Point(-INSET * 10, -INSET*10, SPHERE_RADIUS * 4),
    Color(1.0, 1.0, 1.0));

  Matrix transform = Scaling(SPHERE_RADIUS, SPHERE_RADIUS, SPHERE_RADIUS);
  s.SetTransform(transform);

  for (int y = -INSET; y < INSET; ++y) {
    for (int x = -INSET; x < INSET; ++x) {
      Ray r = Ray(Point(x, y, SPHERE_RADIUS * 3), Vector(0, 0, -1));
      Intersections xs = s.Intersect(r);
      std::optional<Intersection> hit = xs.Hit();
      if (hit.has_value()) {
        Tuple hit_point = r.Position(hit.value().T());
        assert(epsilon_eq(hit_point.x(), x));
        assert(epsilon_eq(hit_point.y(), y));

        DrawHit(canvas, r, hit.value(), light);
      } else {
        // Any intersections should have positive T.
        assert(xs.Size() == 0);
      }
    }
  }

  PPMWriter ppm_writer = PPMWriter(canvas);
  ppm_writer.WriteFile("sphere_lit.ppm");

  return 0;
}

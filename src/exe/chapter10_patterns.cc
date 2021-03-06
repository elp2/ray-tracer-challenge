#include "display/canvas.h"
#include "images/png_writer.h"
#include "lights/point_light.h"
#include "patterns/blended_pattern.h"
#include "patterns/gradient_pattern.h"
#include "patterns/perturbed_pattern.h"
#include "patterns/ring_pattern.h"
#include "patterns/striped_pattern.h"
#include "primitives/math.h"
#include "primitives/matrix.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"
#include "scene/camera.h"
#include "scene/view_transformation.h"
#include "scene/world.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"

#include <cassert>
#include <cmath>
#include <iostream>

const int CAMERA_DIMENSION = 200;

Camera get_camera() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(4.0, 4.0, 2.0);
  Tuple to = Point(0.0, 0.0, 0.0);
  Tuple up = Vector(0.0, 0.0, 1.0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_world() {
  World w = World();
  w.set_light(new PointLight(Point(6.0, 5.0, 1.0), Color(1.0, 1.0, 1.0)));

  auto p = new Plane();
  p->SetTransform(RotationX(M_PI / 2.0));
  auto stripe1 = new StripedPattern(Color(1, 1, 1), Color(1, 0, 0));
  auto stripe2 = new StripedPattern(Color(1, 1, 1), Color(0, 0, 1));
  stripe2->set_transform(RotationZ(M_PI / 2.0));
  auto blended = new BlendedPattern(stripe1, stripe2);
  auto pm1 = Material();
  auto perturbed_plane = new PerturbedPattern(blended);
  pm1.set_pattern(perturbed_plane);
  p->set_material(pm1);
  w.add_object(p);

  auto s1 = new Sphere();
  s1->SetTransform(Translation(0.0, 0.0, 1.0));
  auto m1 = Material();
  m1.set_color(Color(0.9, 0.1, 0.1));
  auto ring_pattern = new RingPattern(Color(1.0, 0.325, 0.286), Color(0.051, 0.596, 0.729));
  ring_pattern->set_transform(Scaling(0.3, 0.3, 0.3));
  auto perturbed_pattern = new PerturbedPattern(ring_pattern);
  m1.set_pattern(perturbed_pattern);
  s1->set_material(m1);
  w.add_object(s1);

  auto s2 = new Sphere();
  s2->SetTransform(Translation(1.5, -1.0, 0.5) * Scaling(0.5, 0.5, 0.5));
  auto m2 = Material();
  m2.set_color(Color(0.1, 0.9, 0.1));
  auto gp = new GradientPattern(Color(1, 0, 0), Color(0, 1, 0));
  m2.set_pattern(gp);
  s2->set_material(m2);
  w.add_object(s2);

  auto s3 = new Sphere();
  s3->SetTransform(Translation(-1.2, 1.3, 0.3) * Scaling(0.3, 0.3, 0.3));
  auto m3 = Material();
  m3.set_color(Color(0.1, 0.1, 0.9));
  s3->set_material(m3);
  w.add_object(s3);

  return w;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  auto canvas = get_camera().Render(get_world());

  PNGWriter png_writer = PNGWriter(canvas);
  png_writer.WriteFile("chapter10_patterns.png");

  return 0;
}

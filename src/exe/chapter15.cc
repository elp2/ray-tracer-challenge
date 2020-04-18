#include "display/canvas.h"
#include "display/ppm_writer.h"
#include "patterns/blended_pattern.h"
#include "patterns/gradient_pattern.h"
#include "patterns/perturbed_pattern.h"
#include "patterns/ring_pattern.h"
#include "patterns/striped_pattern.h"
#include "patterns/three_d_pattern.h"
#include "primitives/math.h"
#include "primitives/matrix.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"
#include "scene/camera.h"
#include "scene/view_transformation.h"
#include "scene/world.h"
#include "shapes/cylinder.h"
#include "shapes/cube.h"
#include "shapes/group.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"
#include "shapes/triangle.h"

#include <cassert>
#include <cmath>
#include <iostream>

const int CAMERA_DIMENSION = 1000;
const float CYLINDER_LENGTH = 4.0;

Camera get_camera1() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(2, 2.0, 3);
  Tuple to = Point(0, 0, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_world1() {
  World w = World();
  w.set_light(PointLight(Point(-8, 8.0, 0.0), Color(1.0, 1.0, 1.0)));

  Material m = Material();
  auto sp = new StripedPattern(PinkColor(), YellowColor());
  sp->set_transform(Scaling(0.25, 0.25, 0.25) * RotationY(M_PI / -3.0));
  m.set_pattern(sp);

  auto p = new Plane();
  p->SetTransform(RotationY(M_PI / 2.0));
  p->set_material(m);
  w.add_object(p);

  Material teal_material = Material();
  teal_material.set_color(TealColor());
  Material silver_material = Material();
  silver_material.set_color(SilverColor());

  Tuple apex = Point(0, 1, 0);
  float s2 = sqrt(2.0) / 2.0;
  auto t1 = new Triangle(Point(-s2, 0, -s2), Point(-s2, 0, s2), apex);
  t1->set_material(teal_material);
  auto t2 = new Triangle(Point(-s2, 0, s2), Point(s2, 0, s2), apex);
  t2->set_material(silver_material);
  auto t3 = new Triangle(Point(s2, 0, s2), Point(s2, 0, -s2), apex);
  t3->set_material(teal_material);
  auto t4 = new Triangle(Point(-s2, 0, -s2), Point(s2, 0, -s2), apex);
  t4->set_material(silver_material);
  w.add_object(t1);
  w.add_object(t2);
  w.add_object(t3);
  w.add_object(t4);

  return w;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  std::cout << "Rendering chapter15_1.ppm." << std::endl;
  Canvas canvas1 = get_camera1().Render(get_world1());
  PPMWriter ppm_writer1 = PPMWriter(&canvas1);
  ppm_writer1.WriteFile("chapter15_1.ppm");

  // std::cout << "Rendering chapter15_2.ppm." << std::endl;
  // Canvas canvas2 = get_camera2().Render(get_world2());
  // PPMWriter ppm_writer2 = PPMWriter(&canvas2);
  // ppm_writer2.WriteFile("chapter15_2.ppm");

  return 0;
}

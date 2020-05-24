#include "display/canvas.h"
#include "images/ppm_writer.h"
#include "lights/point_light.h"
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

#include <cassert>
#include <cmath>
#include <iostream>

const int CAMERA_DIMENSION = 100;
const float CYLINDER_LENGTH = 4.0;

Camera get_camera1() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(0, 5.0, 0);
  Tuple to = Point(2, 0, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_world1() {
  World w = World();
  w.set_light(new PointLight(Point(-8, 8.0, 0.0), Color(1.0, 1.0, 1.0)));

  Material m = Material();
  auto sp = new StripedPattern(PinkColor(), YellowColor());
  sp->set_transform(Scaling(0.25, 0.25, 0.25) * RotationY(M_PI / -3.0));
  m.set_pattern(sp);

  auto p = new Plane();
  p->SetTransform(RotationY(M_PI / 2.0));
  p->set_material(m);
  w.add_object(p);

  auto g = new Group();
  g->SetTransform(Translation(4, 0, 0) * RotationY(M_PI / 4.0));
  w.add_object(g);

  auto s1 = new Sphere();
  s1->set_material(m);
  g->AddChild(s1);

  auto s2 = new Sphere();
  s2->SetTransform(RotationY(M_PI / 4.0));
  s2->set_material(m);
  w.add_object(s2);

  return w;
}

Camera get_camera2() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(0, 10, 10);
  Tuple to = Point(0, 0, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

Group *get_arm() {
  auto arm = new Group();
  auto sphere = new Sphere();
  arm->AddChild(sphere);

  auto cylinder = new Cylinder(CYLINDER_LENGTH, 0, true);
  cylinder->SetTransform(RotationZ(M_PI / 2.0));
  arm->AddChild(cylinder);

  auto sphere2 = new Sphere();
  sphere2->SetTransform(Translation(-CYLINDER_LENGTH, 0, 0));
  arm->AddChild(sphere2);

  return arm;
}

World get_world2() {
  World w = World();
  w.set_light(new PointLight(Point(5.0, 2.0, 20.0), Color(1.0, 1.0, 1.0)));

  Material m = Material();
  auto sp = new StripedPattern(PinkColor(), YellowColor());
  sp->set_transform(Scaling(0.25, 0.25, 0.25) * RotationY(M_PI / -3.0));
  m.set_pattern(sp);

  auto p = new Plane();
  p->SetTransform(RotationY(M_PI / 2.0));
  p->set_material(m);
  w.add_object(p);

  for (int i = 0; i < 6; ++i) {
    auto arm = get_arm();
    arm->SetTransform(RotationY((float) i * M_PI / 3.0) * Translation(CYLINDER_LENGTH / 2.0, 0, CYLINDER_LENGTH));
    w.add_object(arm);
  }

  return w;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  // Material tests.
  // std::cout << "Rendering chapter14_1.ppm." << std::endl;
  // auto canvas1 = get_camera1().Render(get_world1());
  // PPMWriter ppm_writer1 = PPMWriter(canvas1);
  // ppm_writer1.WriteFile("chapter14_1.ppm");

  std::cout << "Rendering chapter14_2.ppm." << std::endl;
  auto canvas2 = get_camera2().Render(get_world2());
  PPMWriter ppm_writer2 = PPMWriter(canvas2);
  ppm_writer2.WriteFile("chapter14_2.ppm");

  return 0;
}

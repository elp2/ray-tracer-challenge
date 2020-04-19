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
#include "shapes/obj_parser.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"
#include "shapes/triangle.h"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>

const int CAMERA_DIMENSION = 100;

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

  auto pyramid = new Group();
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
  pyramid->AddChild(t1);
  pyramid->AddChild(t2);
  pyramid->AddChild(t3);
  pyramid->AddChild(t4);
  w.add_object(pyramid);

  return w;
}

Camera get_camera2() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(0, 3, -12);
  Tuple to = Point(0, 0, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_world2() {
  World w = World();
  w.set_light(PointLight(Point(0, 5, 0), Color(1.0, 1.0, 1.0)));

  std::ifstream model("teapot.obj");
  assert(model.is_open());
  std::stringstream ss;
  ss << model.rdbuf();
  model.close();

  auto parser = ObjParser(ss);
  Material teapot_material = Material();
  teapot_material.set_shininess(150);
  teapot_material.set_color(Color(0.4, 0, 0));
  teapot_material.set_reflective(0.3);
  parser.set_material(teapot_material);
  auto parsed_group = parser.DefaultGroup()->OptimizedSubgroups(10);
  //auto parsed_group = parser.GroupNamed("Teapot001")->OptimizedSubgroups(5);
  w.add_object(parsed_group);

  auto teapot2 = parser.DefaultGroup()->OptimizedSubgroups(10);
  teapot2->SetTransform(Translation(2, 0, -2) * Scaling(0.5, 0.5, 0.5) * RotationY(M_PI / 4.0));
  w.add_object(teapot2);

  auto p = new Plane();
  Material m = Material();
  m.set_color(ElectricBlueColor());
  m.set_reflective(0.6);
  p->set_material(m);
  w.add_object(p);

  auto sphere = new Sphere();
  sphere->SetTransform(Translation(-2, 2, -4) * Scaling(1.5, 1.5, 1.5));
  Material sm = m;
  sm.set_reflective(1.0);
  sphere->set_material(sm);
  w.add_object(sphere);

  return w;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  // std::cout << "Rendering chapter15_1.ppm." << std::endl;
  // Canvas canvas1 = get_camera1().Render(get_world1());
  // PPMWriter ppm_writer1 = PPMWriter(&canvas1);
  // ppm_writer1.WriteFile("chapter15_1.ppm");

  std::cout << "Rendering chapter15_2.ppm." << std::endl;
  Canvas canvas2 = get_camera2().Render(get_world2());
  PPMWriter ppm_writer2 = PPMWriter(&canvas2);
  ppm_writer2.WriteFile("chapter15_2.ppm");

  return 0;
}

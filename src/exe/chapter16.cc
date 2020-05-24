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
#include "shapes/constructive_solid_geometry.h"
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

ConstructiveSolidGeometry *Dice(Color c) {
  const float dice_radius = 5;
  // const float dice_curve_diff = 0.3;
  const float dice_scaling= 4; // sqrt(dice_curve_diff + dice_radius);

  Material dice_material;
  dice_material.set_color(c);

  Sphere *dice_sphere = new Sphere();
  dice_sphere->SetTransform(Scaling(dice_radius, dice_radius, dice_radius));
  dice_sphere->set_material(dice_material);
  Cube *dice_cube = new Cube();
  dice_cube->SetTransform(Scaling(dice_scaling, dice_scaling, dice_scaling));
  dice_cube->set_material(dice_material);

  auto csg = new ConstructiveSolidGeometry(dice_sphere, dice_cube,
      new IntersectIntersectionStrategy());

  return csg;
}

Camera get_camera1() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(3, 8, -8);
  Tuple to = Point(0, 0, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_world1() {
  World w = World();
  w.set_light(new PointLight(Point(-8, 15, -5), Color(1.0, 1.0, 1.0)));

  w.add_object(Dice(Color(ElectricBlueColor())));
  return w;
}

Camera get_camera2() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(0, 20, -50);
  Tuple to = Point(0, 10, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_world2() {
  World w = World();
  w.set_light(new PointLight(Point(-8, 15, -5), Color(1.0, 1.0, 1.0)));

  std::ifstream model("teapot-low.obj");
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
  //auto parsed_group = parser.DefaultGroup()->OptimizedSubgroups(10);
  auto parsed_group = parser.GroupNamed("Teapot001")->OptimizedSubgroups(5);
  Matrix adjust_teapot = RotationX(-M_PI / 2);
  parsed_group->SetTransform(adjust_teapot);
  w.add_object(parsed_group);

  auto teapot2 = parser.GroupNamed("Teapot001")->OptimizedSubgroups(5);
  teapot2->SetTransform(Translation(10, 0, -10) * Scaling(0.25, 0.25, 0.25)
      * RotationY(M_PI / 4.0) * adjust_teapot);
  w.add_object(teapot2);

  auto floor = new Plane();
  Material m = Material();
  m.set_color(Color(0.525, 0.514, 0.412));
  m.set_reflective(0.1);
  floor->set_material(m);
  w.add_object(floor);

  auto left_wall = new Plane();
  Material lm = Material();
  lm.set_color(Color(0.58, 0.286, 0.298));
  lm.set_reflective(0.1);
  left_wall->SetTransform(Translation(-15, 0, 0) * RotationZ(M_PI / 2.0));
  left_wall->set_material(lm);
  w.add_object(left_wall);

  auto right_wall = new Plane();
  Material rm = Material();
  rm.set_color(Color(0.297, 0.287, 0.58));
  rm.set_reflective(0.1);
  right_wall->SetTransform(Translation(15, 0, 0) * RotationZ(M_PI / 2.0));
  right_wall->set_material(rm);
  w.add_object(right_wall);

  auto ceiling = new Plane();
  Material cm = Material();
  cm.set_color(Color(0.525, 0.514, 0.412));
  cm.set_reflective(0.1);
  ceiling->set_material(cm);
  ceiling->SetTransform(Translation(0, 25, 0));
  w.add_object(ceiling);

  auto back = new Plane();
  Material bm = Material();
  bm.set_color(Color(0.365, 0.337, 0.337));
  bm.set_reflective(0.3);
  bm.set_diffuse(1.0);
  bm.set_shininess(100);
  back->set_material(bm);
  back->SetTransform(Translation(0, 0, 10) * RotationX(M_PI / 2.0));
  w.add_object(back);

  auto sphere = new Sphere();
  sphere->SetTransform(Translation(-4, 4, -20) * Scaling(4, 4, 4));
  Material sm;
  sm.set_color(ElectricBlueColor());
  sm.set_reflective(1.0);
  sphere->set_material(sm);
  w.add_object(sphere);

  auto lens1 = GlassySphere();
  lens1->SetTransform(Translation(5, 10, -22) * Scaling(4, 4, 4));
  auto lens2 = GlassySphere();
  lens2->SetTransform(Translation(5, 10, -20) * Scaling(4, 4, 4));

  auto csg = new ConstructiveSolidGeometry(lens1, lens2, new IntersectIntersectionStrategy());
  w.add_object(csg);

  return w;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  std::cout << "Rendering chapter16_1.ppm." << std::endl;
  auto canvas1 = get_camera1().Render(get_world1());
  PPMWriter ppm_writer1 = PPMWriter(canvas1);
  ppm_writer1.WriteFile("chapter16_1.ppm");

  // std::cout << "Rendering chapter16_2.ppm." << std::endl;
  // Canvas canvas2 = get_camera2().Render(get_world2());
  // PPMWriter ppm_writer2 = PPMWriter(canvas2);
  // ppm_writer2.WriteFile("chapter16_2.ppm");

  return 0;
}

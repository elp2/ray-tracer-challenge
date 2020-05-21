#include "display/canvas.h"
#include "display/ppm_writer.h"
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
#include "shapes/cone.h"
#include "shapes/cylinder.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"

#include <cassert>
#include <cmath>
#include <iostream>

const int CAMERA_DIMENSION = 100;

Camera get_camera1() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(-160, 40.0, 0.0);
  Tuple to = Point(0.0, 6.0, 30.0);
  Tuple up = Vector(0.0, 10.0, 0.0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_world1() {
  World w = World();
  w.set_light(new PointLight(Point(-80, 80, 0.0), Color(1.0, 1.0, 1.0)));

  auto p = new Plane();
  Material pm1;
  auto stripe1 = new StripedPattern(Color(0.5234, 0.3711, 0.2617),
      Color(0.6078, 0.4627, 0.3255));
  stripe1->set_transform(Scaling(2.5, 6, 2.5) * RotationY(M_PI / 3));
  auto perturbed_plane = new PerturbedPattern(stripe1);
  pm1.set_pattern(perturbed_plane);
  pm1.set_reflective(0.2);
  pm1.set_shininess(100);
  p->set_material(pm1);
  w.add_object(p);

  Cylinder *blue_cylinder = new Cylinder();
  blue_cylinder->SetTransform(Scaling(10, 10, 10));
  Material m = Material();
  m.set_color(ElectricBlueColor());
  m.set_reflective(0.3);
  blue_cylinder->set_material(m);
  w.add_object(blue_cylinder);

  Cylinder *yellow_cylinder = new Cylinder(30, 0, true);
  yellow_cylinder->SetTransform(Scaling(20, 20, 20) * Translation(-40, 0, 10));
  Material my = Material();
  my.set_color(YellowColor());
  my.set_reflective(0.3);
  yellow_cylinder->set_material(my);
  w.add_object(yellow_cylinder);

  Cone *cone = new Cone();
  cone->SetTransform(Translation(30, 30, 30));
  w.add_object(cone);

  return w;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  std::cout << "Rendering chapter13.ppm." << std::endl;
  auto canvas1 = get_camera1().Render(get_world1());
  PPMWriter ppm_writer1 = PPMWriter(canvas1);
  ppm_writer1.WriteFile("chapter13.ppm");

  return 0;
}

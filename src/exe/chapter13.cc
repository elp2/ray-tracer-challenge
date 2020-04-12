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
#include "shapes/plane.h"
#include "shapes/sphere.h"

#include <cassert>
#include <cmath>
#include <iostream>

const int CAMERA_DIMENSION = 100;

Camera get_camera1() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(-16, 4.0, 0.0);
  Tuple to = Point(0.0, 6.0, 3.0);
  Tuple up = Vector(0.0, 1.0, 0.0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

Shape *Cyl(Color c, int y, int z) {
  Cylinder *cylinder = new Cylinder();

  Material m = Material();
  m.set_color(c);
  m.set_reflective(0.3);
  cylinder->set_material(m);

  return cylinder;
}

World get_world1() {
  World w = World();
  w.set_light(PointLight(Point(-8, 8.0, 0.0), Color(1.0, 1.0, 1.0)));

  auto p = new Plane();
  Material pm1;
  auto stripe1 = new StripedPattern(Color(0.5234, 0.3711, 0.2617),
      Color(0.6078, 0.4627, 0.3255));
  stripe1->set_transform(Scaling(0.25, 0.6, 0.25) * RotationY(M_PI / 3));
  auto perturbed_plane = new PerturbedPattern(stripe1);
  pm1.set_pattern(perturbed_plane);
  pm1.set_reflective(0.2);
  pm1.set_shininess(100);
  p->set_material(pm1);
  w.add_object(p);

  w.add_object(Cyl(ElectricBlueColor(), 0, 0));

  return w;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  std::cout << "Rendering chapter13.ppm." << std::endl;
  Canvas canvas1 = get_camera1().Render(get_world1());
  PPMWriter ppm_writer1 = PPMWriter(&canvas1);
  ppm_writer1.WriteFile("chapter13.ppm");

  return 0;
}
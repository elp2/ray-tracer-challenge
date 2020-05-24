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
#include "shapes/cube.h"
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

Shape *Domino(Color c, int y, int z) {
  Cube *cube = new Cube();

  const float size = 0.95;
  cube->SetTransform(Translation(0, y * 2.0 + 2, z * 2.0)
      * Scaling(size, size, size));

  Material m = Material();
  m.set_color(c);
  m.set_reflective(0.3);
  cube->set_material(m);
  
  return cube;
}

World get_world1() {
  World w = World();
  w.set_light(new PointLight(Point(-8, 8.0, 0.0), Color(1.0, 1.0, 1.0)));

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

  w.add_object(Domino(YellowColor(), 0, 0));
  w.add_object(Domino(YellowColor(), 1, 0));
  w.add_object(Domino(YellowColor(), 2, 0));
  w.add_object(Domino(YellowColor(), 0, 1));

  w.add_object(Domino(ElectricBlueColor(), 0, 2));
  w.add_object(Domino(ElectricBlueColor(), 1, 2));
  w.add_object(Domino(ElectricBlueColor(), 2, 2));
  w.add_object(Domino(ElectricBlueColor(), 1, 1));

  w.add_object(Domino(PinkColor(), 0, 3));
  w.add_object(Domino(PinkColor(), 1, 3));
  w.add_object(Domino(PinkColor(), 2, 3));
  w.add_object(Domino(PinkColor(), 3, 3));

  w.add_object(Domino(OrangeColor(), 4, 0));
  w.add_object(Domino(OrangeColor(), 4, 1));
  w.add_object(Domino(OrangeColor(), 4, 2));
  w.add_object(Domino(OrangeColor(), 3, 1));

  return w;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  std::cout << "Rendering chapter12_1.ppm." << std::endl;
  auto canvas1 = get_camera1().Render(get_world1());
  PPMWriter ppm_writer1 = PPMWriter(canvas1);
  ppm_writer1.WriteFile("chapter12_1.ppm");

  return 0;
}

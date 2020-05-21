#include "display/canvas.h"
#include "display/png_writer.h"
#include "lights/point_light.h"
#include "patterns/blended_pattern.h"
#include "patterns/gradient_pattern.h"
#include "patterns/perturbed_pattern.h"
#include "patterns/ring_pattern.h"
#include "patterns/striped_pattern.h"
#include "patterns/three_d_pattern.h"
#include "primitives/math.h"
#include "primitives/matrix.h"
#include "primitives/perlin_noise.h"
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

const int CAMERA_DIMENSION = 300;

Camera get_camera1() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(6, 4, -1);
  Tuple to = Point(0, 0, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_world1() {
  World w = World();
  w.set_light(new PointLight(Point(3, 5, 5), Color(1.0, 1.0, 1.0)));

  auto *s = new Sphere();
  s->SetTransform(Translation(0.5, 1, 0));
  w.add_object(s);

  auto *c = new Cube();
  Material cm = Material();
  cm.set_color(Color(0.3, 0.3, 0.3));
  cm.set_reflective(1.0);
  c->SetTransform(Translation(-2.5, 2, -0.5));
  c->set_material(cm);
  w.add_object(c);

  auto *plane = new Plane();
  w.add_object(plane);

  return w;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  std::cout << "Rendering new_lights.png." << std::endl;
  auto canvas1 = get_camera1().Render(get_world1());
  PNGWriter ppm_writer1 = PNGWriter(canvas1);
  ppm_writer1.WriteFile("new_lights.png");

  return 0;
}
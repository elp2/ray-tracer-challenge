#include "display/canvas.h"
#include "display/png_writer.h"
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

const int CAMERA_DIMENSION = 200;

Camera get_camera1() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(5, 3, -1);
  Tuple to = Point(0, 0, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_world1() {
  World w = World();
  w.set_light(PointLight(Point(3, 5, 5), Color(1.0, 1.0, 1.0)));

  auto *s = new Sphere();
  Material m = Material();
  m.set_color(Color(0.8, 0, 0));
  m.set_reflective(1.0);
  // auto *sp = new StripedPattern(YellowColor(), ElectricBlueColor());
  // sp->set_transform(Scaling(0.3, 0.5, 0.15));
  // m.set_pattern(sp);
  // PerturbedPattern *pp = new PerturbedPattern(sp);
  // m.set_pattern(pp);
  s->set_material(m);
  s->SetTransform(Translation(0.5, 1, 0));
  s->set_normal_noise(new PerlinNoise());
  w.add_object(s);

  auto *c = new Cube();
  Material cm = Material();
  cm.set_color(Color(0.3, 0.3, 0.3));
  cm.set_reflective(1.0);
  c->SetTransform(Translation(-2.5, 1.5, -0.5));
  // c->set_normal_noise(new PerlinNoise());
  c->set_material(cm);
  w.add_object(c);


  auto *plane = new Plane();
  auto pm = Material();
  pm.set_reflective(0.8);
  pm.set_color(Color(0.3, 0.3, 0.3));
  plane->set_material(pm);
  w.add_object(plane);

  return w;
}

void write_noise() {
  auto noise = new PerlinNoise();
  const int DIMENSION = 100;
  auto nc = new Canvas(DIMENSION, DIMENSION);
  for (int y = 0; y < DIMENSION; ++y) {
    for (int x = 0; x < DIMENSION; ++x) {
      float pvx = 9 * (float)x / (float)DIMENSION;
      float pvy = 3 * (float)y / (float)DIMENSION;
      float pn = noise->PerlinValue(Point(pvx, pvy, 0.1));
      pn += 0.1;
      if (pn < 0 || pn > 1) {
        std::cout << pn << " ";
      }
      // assert(pn >= 0);
      // assert(pn <= 1.0);
      nc->WritePixel(Color(pn, 0, 0), x, y);
    }
    std::cout << std::endl;
  }
  PNGWriter writer = PNGWriter(nc);
  writer.WriteFile("noise.png");
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  srand(time(NULL));
  write_noise();

  std::cout << "Rendering perturbed_normals.ppm." << std::endl;
  auto canvas1 = get_camera1().Render(get_world1());
  PNGWriter ppm_writer1 = PNGWriter(canvas1);
  ppm_writer1.WriteFile("perturbed_normals.png");

  return 0;
}

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
#include "shapes/cube.h"
#include "shapes/group.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"

#include <cassert>
#include <cmath>
#include <iostream>

const int CAMERA_DIMENSION = 200;

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
  w.set_light(PointLight(Point(-8, 8.0, 0.0), Color(1.0, 1.0, 1.0)));

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

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  std::cout << "Rendering chapter14_1.ppm." << std::endl;
  Canvas canvas1 = get_camera1().Render(get_world1());
  PPMWriter ppm_writer1 = PPMWriter(&canvas1);
  ppm_writer1.WriteFile("chapter14_1.ppm");

  return 0;
}

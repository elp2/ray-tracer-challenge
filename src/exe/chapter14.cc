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
  Tuple from = Point(1.5, 2.0, 0);
  Tuple to = Point(2, 0, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_world1() {
  World w = World();
  w.set_light(PointLight(Point(-8, 8.0, 0.0), Color(1.0, 1.0, 1.0)));

  auto g = new Group();
  g->SetTransform(Translation(4, 0, 0) * RotationY(M_PI / 4.0));
  auto c1 = new Cube();
  g->AddChild(c1);
  auto c2 = new Cube();
  c2->SetTransform(RotationY(M_PI / 4.0));
  Material m = Material();
  auto sp = new StripedPattern(PinkColor(), YellowColor());
  m.set_pattern(sp);
  c1->set_material(m);
  c2->set_material(m);

  w.add_object(g);
  w.add_object(c2);

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

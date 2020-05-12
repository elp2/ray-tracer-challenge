#include "display/canvas.h"
#include "display/ppm_writer.h"
#include "primitives/math.h"
#include "primitives/matrix.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"
#include "scene/camera.h"
#include "scene/view_transformation.h"
#include "scene/world.h"
#include "shapes/sphere.h"

#include <cassert>
#include <cmath>
#include <iostream>

const int CAMERA_DIMENSION = 300;

Camera get_camera() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(0.0, 1.5, -5.0);
  Tuple to = Point(0.0, 1.0, 0.0);
  Tuple up = Vector(0.0, 1.0, 0.0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

Sphere *get_wall(Color c) {
  auto wall = new Sphere();
  Material m = Material();
  m.set_color(c);
  m.set_specular(0.0);
  wall->set_material(m);
  return wall;
}

World get_world() {
  World w = World();
  w.set_light(PointLight(Point(-10.0, 10.0, -10.0), Color(1.0, 1.0, 1.0)));

  auto floor = get_wall(Color(1.0, 0.9, 0.9));
  floor->SetTransform(Scaling(20.0, 0.001, 20.0));
  w.add_object(floor);

  auto right_wall = get_wall(Color(1.0, 0.5, 0.5));
  right_wall->SetTransform(Translation(0.0, 0.0, 5.0) * RotationY(M_PI / 4.0) * RotationX(M_PI / 2.0) * Scaling(10.0, 0.01, 10.0));
  w.add_object(right_wall);

  auto left_wall = get_wall(Color(1.0, 0.5, 0.5));
  left_wall->SetTransform(Translation(0.0, 0.0, 5.0) * RotationY(-M_PI / 4.0) * RotationX(M_PI / 2.0) * Scaling(10.0, 0.01, 10.0));
  w.add_object(left_wall);

  float snowball_radius = 0.66;
  float height = snowball_radius;
  for (int ball = 0; ball < 3; ++ball) {
    auto snowball = get_wall(Color(1.0, 1.0, 1.0));
    snowball->SetTransform(Translation(0.0, height, 0.0)
      * Scaling(snowball_radius, snowball_radius, snowball_radius));
    w.add_object(snowball);
    height += snowball_radius;
    snowball_radius *= 0.66;
    height += snowball_radius;
  }

  return w;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  auto canvas = get_camera().Render(get_world());

  PPMWriter ppm_writer = PPMWriter(canvas);
  ppm_writer.WriteFile("chapter7.ppm");

  return 0;
}

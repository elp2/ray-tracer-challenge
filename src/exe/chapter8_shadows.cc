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
  Tuple from = Point(2.5, 2.5, 2.5);
  Tuple to = Point(0.0, 0.0, 0.0);
  Tuple up = Vector(0.0, 1.0, 0.0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

Sphere get_wall(Color c) {
  Sphere wall = Sphere();
  Material m = Material();
  m.set_color(c);
  m.set_specular(0.0);
  wall.set_material(m);
  return wall;
}

World get_world() {
  World w = World();
  w.set_light(PointLight(Point(20.0, 16.0, 0.0), Color(1.0, 1.0, 1.0)));

  Sphere earth = Sphere();
  Material em = Material();
  em.set_color(Color(0.0, 0.0, 1.0));
  earth.set_material(em);
  w.add_object(earth);

  Sphere moon = Sphere();
  moon.SetTransform(Translation(1.25, 1.25, 0.0) * Scaling(0.25, 0.25, 0.25));
  Material mm = Material();
  mm.set_color(Color(0.8, 0.8, 0.8));
  mm.set_shininess(10.0);
  moon.set_material(mm);
  w.add_object(moon);

  return w;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  Canvas canvas = get_camera().Render(get_world());

  PPMWriter ppm_writer = PPMWriter(&canvas);
  ppm_writer.WriteFile("chapter8_shadows.ppm");

  return 0;
}
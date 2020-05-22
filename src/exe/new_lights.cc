#include "display/canvas.h"
#include "display/png_writer.h"
#include "lights/area_light.h"
#include "lights/point_light.h"
#include "lights/spot_light.h"
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
  Tuple from = Point(6, 4, -1);
  Tuple to = Point(0, 0, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

Camera get_camera2() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(4, 16, 0);
  Tuple to = Point(0, 0, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_cube_world(Light *light) {
  World w = World();
  w.set_light(light);

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

World get_world(Light *light) {
  World w = World();
  w.set_light(light);

  auto *s = new Cube();
  s->SetTransform(Translation(0, 1, 0));
  w.add_object(s);


  auto *plane = new Plane();
  w.add_object(plane);

  return w;
}

void render_cube_worlds() {
  Tuple position =  Point(3, 5, 5);
  Color intensity = Color(1.0, 1.0, 1.0);

  std::cout << "Rendering point_light.png." << std::endl;
  auto canvas1 = get_camera1().Render(get_cube_world(new PointLight(position, intensity)));
  PNGWriter ppm_writer1 = PNGWriter(canvas1);
  ppm_writer1.WriteFile("point_light.png");

  std::cout << "Rendering area_light.png." << std::endl;
  auto canvas2 = get_camera1().Render(get_cube_world(new AreaLight(position, intensity, 0.1, 3)));
  PNGWriter ppm_writer2 = PNGWriter(canvas2);
  ppm_writer2.WriteFile("area_light.png");

  std::cout << "Rendering spot_light.png." << std::endl;
  auto canvas3 = get_camera1().Render(get_cube_world(
      new SpotLight(position, intensity, DEFAULT_CENTER_RADIANS, DEFAULT_TOTAL_RADIANS, Point(0, 0, 0))));
  PNGWriter ppm_writer3 = PNGWriter(canvas3);
  ppm_writer3.WriteFile("spot_light.png");
}

void render_bugfix_world() {
  // The cube is 2 tall, so no light should fall behind the cube when light position y=1.5.
  // However, it clearly does on the area light.
  // This should be easily testable by seeing how we calculate the color for (100, 0).
  Tuple position =  Point(4, 1.5, 0);
  Color intensity = Color(1.0, 1.0, 1.0);

  std::cout << "Rendering point_light.png." << std::endl;
  auto canvas1 = get_camera2().Render(get_world(new PointLight(position, intensity)));
  PNGWriter ppm_writer1 = PNGWriter(canvas1);
  ppm_writer1.WriteFile("point_light.png");

  std::cout << "Rendering area_light.png." << std::endl;
  auto canvas2 = get_camera2().Render(get_world(new AreaLight(position, intensity, 0.2, 2)));
  PNGWriter ppm_writer2 = PNGWriter(canvas2);
  ppm_writer2.WriteFile("area_light.png");
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  render_cube_worlds();
  // render_bugfix_world();

  return 0;
}

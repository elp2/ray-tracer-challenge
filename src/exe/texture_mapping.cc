#include "display/canvas.h"
#include "images/png_file.h"
#include "images/png_reader.h"
#include "images/png_writer.h"
#include "lights/area_light.h"
#include "lights/point_light.h"
#include "lights/spot_light.h"
#include "patterns/blended_pattern.h"
#include "patterns/gradient_pattern.h"
#include "patterns/perturbed_pattern.h"
#include "patterns/ring_pattern.h"
#include "patterns/striped_pattern.h"
#include "patterns/texture_pattern.h"
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

World get_cube_world(Light *light) {
  World w = World();
  w.set_light(light);

  float cs = 0.5;
  auto *scbroken = new Sphere();
  scbroken->SetTransform(Translation(0.5, 1, 2));
  auto scbrokenp = new ThreeDPattern(Color(1, 0, 0), Color(0, 0, 0));
  scbrokenp->set_transform(Scaling(cs, cs, cs));
  auto scbrokenm = Material();
  scbrokenm.set_pattern(scbrokenp);
  scbroken->set_material(scbrokenm);
  w.add_object(scbroken);

  auto *sc = new Sphere();
  sc->SetTransform(Translation(0.5, 1, 0));

  PNGReader reader = PNGReader();
  auto scp_png = reader.ReadFile("2x2.png");
  auto scp = new TexturePattern(scp_png->width(), scp_png->height(), scp_png->pixels(), false);
  scp->set_transform(Scaling(cs, cs, cs));
  auto scm = Material();
  scm.set_uv_pattern(scp);
  sc->set_material(scm);
  w.add_object(sc);

  auto *c = new Cube();
  Material cm = Material();
  cm.set_color(Color(0.3, 0.3, 0.3));
  cm.set_reflective(1.0);
  c->SetTransform(Translation(-2.5, 2, -0.5));
  c->set_material(cm);
  w.add_object(c);

  auto *plane = new Plane();
  PNGReader plane_reader = PNGReader();
  auto plane_png = reader.ReadFile("2x2.png");
  auto plane_texture = new TexturePattern(plane_png->width(), plane_png->height(), plane_png->pixels(), false);
  auto scplane = Material();
  scplane.set_pattern(plane_texture);
  plane->set_material(scplane);
  w.add_object(plane);

  return w;
}

void render_worlds() {
  Tuple position =  Point(3, 5, 5);
  Color intensity = Color(1.0, 1.0, 1.0);

  std::cout << "Rendering texture_mapping.png." << std::endl;
  auto canvas1 = get_camera1().Render(get_cube_world(new PointLight(position, intensity)));
  PNGWriter ppm_writer1 = PNGWriter(canvas1);
  ppm_writer1.WriteFile("texture_mapping.png");
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  render_worlds();

  return 0;
}

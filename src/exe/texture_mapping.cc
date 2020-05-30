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
  auto scp_png = reader.ReadFile("earth_medium.png");
  auto scp = new TexturePattern(scp_png->width(), scp_png->height(), scp_png->pixels(), false);
  // scp->set_transform(Scaling(cs, cs, cs));
  auto scm = Material();
  scm.set_uv_pattern(scp);
  sc->set_material(scm);
  w.add_object(sc);

  auto *sc2 = new Sphere();
  sc2->SetTransform(Translation(0.5, 1, -1.5) * RotationY(1.2 * M_PI));
  auto sc2p_png = reader.ReadFile("earth_medium.png");
  auto sc2p = new TexturePattern(sc2p_png->width(), sc2p_png->height(), sc2p_png->pixels(), false);
  // sc2p->set_transform(Sc2aling(cs, cs, cs));
  auto sc2m = Material();
  sc2m.set_uv_pattern(sc2p);
  sc2->set_material(sc2m);
  w.add_object(sc2);

  auto *c = new Cube();
  Material cm = Material();
  cm.set_color(Color(0.3, 0.3, 0.3));
  cm.set_reflective(1.0);
  c->SetTransform(Translation(-2.5, 2, -0.5) * Scaling(2, 2, 2));
  c->set_material(cm);
  w.add_object(c);

  auto *plane = new Plane();
  PNGReader plane_reader = PNGReader();
  // auto plane_png = reader.ReadFile("earth_medium.png");
  // auto plane_texture = new TexturePattern(plane_png->width(), plane_png->height(), plane_png->pixels(), false);
  // plane_texture->set_transform(Scaling(3, 3, 3));
  auto scplane = Material();
  // scplane.set_pattern(plane_texture);
  scplane.set_reflective(0.7);
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

void render_world_world() {
  float fromx = 3;
  float fromz = 3;
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(fromx, 1.5, fromz);
  Tuple to = Point(0, 1, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));

  Tuple position =  Point(fromx, 1.5, fromz);
  Color intensity = Color(1.0, 1.0, 1.0);

  World w = World();
  w.set_light(new PointLight(position, intensity));

  auto *sc = new Sphere();
  sc->SetTransform(Translation(0, 1, 0));
  PNGReader reader = PNGReader();
  auto scp_png = reader.ReadFile("debug_texture.png");
  auto scp = new TexturePattern(scp_png->width(), scp_png->height(), scp_png->pixels(), false);
  // scp->set_transform(Scaling(cs, cs, cs));
  auto scm = Material();
  scm.set_uv_pattern(scp);
  sc->set_material(scm);
  w.add_object(sc);

  std::cout << "Rendering world_world.png." << std::endl;
  auto canvas1 = c.Render(w);
  PNGWriter ppm_writer1 = PNGWriter(canvas1);
  ppm_writer1.WriteFile("world_world.png");
}

void test_png() {
  Canvas *c = new Canvas(5, 5);
  for (int y = 0; y < 5; ++y) {
    for (int x = 0; x < 5; ++x) {
      c->WritePixel(Color(0, 0, 1), x, y);
    }
  }
  PNGWriter *writer = new PNGWriter(c);
  writer->WriteFile("elpblue.png");

  PNGReader earth_reader = PNGReader();
  auto earth_png = earth_reader.ReadFile("earth_medium.png");
  Canvas *earth_canvas = new Canvas(500, 500);

  std::vector<Color> *pixels = earth_png->pixels();
  for (int y = 0; y < 500; ++y) {
    for (int x = 0; x < 500; ++x) {
      earth_canvas->WritePixel((*pixels)[x + y * 500], x, y);
    }
  }
  PNGWriter *earth_writer = new PNGWriter(earth_canvas);
  earth_writer->WriteFile("elp_earth.png");
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  // test_png();
  render_worlds();
  // render_world_world();

  return 0;
}

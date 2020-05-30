#include "display/canvas.h"
#include "images/png_writer.h"
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

Camera get_camera1(bool supersample) {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0, supersample);
  Tuple from = Point(6, 4, -1);
  Tuple to = Point(0, 0, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

Group *get_pawn() {
  std::ifstream model("chess.obj");
  assert(model.is_open());
  std::stringstream ss;
  ss << model.rdbuf();
  model.close();

  ObjParser *parser = new ObjParser(ss);
  auto g = parser->GroupNamed("PEDONE12")->OptimizedSubgroups(5);
  Matrix scaling = Scaling(1.0 / 600.0, 1.0 / 600.0, 1.0 / 600.0);
  g->SetTransform(scaling * Translation(0, 3, 0));
  return g;
}

World get_world(Light *light) {
  World w = World();
  w.set_light(light);

  auto s = new Sphere();
  w.add_object(s);

  auto *pawn = get_pawn();
  w.add_object(pawn);

  auto *chessboard = new Plane();
  auto chessboard_pattern = new ThreeDPattern(WhiteColor(), BlackColor());
  auto chessboard_material = Material();
  chessboard_material.set_reflective(0.4);
  chessboard_material.set_pattern(chessboard_pattern);
  chessboard->set_material(chessboard_material);
  w.add_object(chessboard);

  return w;
}

void render_chessboard() {
  Tuple position =  Point(3, 5, 5);
  Color intensity = Color(1.0, 1.0, 1.0);

  // std::cout << "Rendering area_light.png." << std::endl;
  // auto canvas2 = get_camera2().Render(get_world(new AreaLight(position, intensity, 0.2, 2)));
  // PNGWriter ppm_writer2 = PNGWriter(canvas2);
  // ppm_writer2.WriteFile("area_light.png");

  std::cout << "Rendering chessboard.png." << std::endl;
  auto canvas2 = get_camera1(false).Render(get_world(new PointLight(position, intensity)));
  PNGWriter ppm_writer2 = PNGWriter(canvas2);
  ppm_writer2.WriteFile("chessboard.png");
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  render_chessboard();

  return 0;
}

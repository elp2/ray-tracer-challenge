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

const int CAMERA_DIMENSION = 600;
const bool SUPER_SAMPLE = true;
const float CHESSBOARD_WIDTH = 2.5;

const Tuple light_position =  Point(3, 5, 5);
const Color light_intensity = Color(1.0, 1, 1);
// Light *LIGHT = new PointLight(light_position, light_intensity);
Light *LIGHT = new SpotLight(light_position, light_intensity, 0.3, 0.5, Point(0, 0, 0));


Camera get_camera1(bool supersample) {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0, supersample);
  Tuple from = Point(12, 8, -2);
  Tuple to = Point(0, 0, 0);
  Tuple up = Vector(0, 1, 0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

Group *get_pawn(float x, float z) {
  std::ifstream model("chess.obj");
  assert(model.is_open());
  std::stringstream ss;
  ss << model.rdbuf();
  model.close();

  ObjParser *parser = new ObjParser(ss);
  auto g = parser->GroupNamed("PEDONE12")->OptimizedSubgroups(5, true, false, true);
  Bounds b = g->UnitBounds();
  g->SetTransform(Translation(x * CHESSBOARD_WIDTH, fabs(b.minimum().y()), z * CHESSBOARD_WIDTH));
  return g;
}

World get_world(Light *light) {
  World w = World();
  w.set_light(light);

  w.add_object(get_pawn(0, 0));
  w.add_object(get_pawn(0, 1));
  w.add_object(get_pawn(0, -1));

  auto *chessboard = new Plane();
  auto chessboard_pattern = new ThreeDPattern(WhiteColor(), BlackColor());
  chessboard_pattern->set_transform(Scaling(CHESSBOARD_WIDTH, CHESSBOARD_WIDTH, CHESSBOARD_WIDTH)
      * Translation(-0.5, -0.5, -0.5));
  auto chessboard_material = Material();
  chessboard_material.set_reflective(0.4);
  chessboard_material.set_pattern(chessboard_pattern);
  chessboard->set_material(chessboard_material);
  w.add_object(chessboard);

  return w;
}

void render_chessboard() {
  std::cout << "Rendering chessboard.png." << std::endl;
  auto canvas2 = get_camera1(SUPER_SAMPLE).Render(get_world(LIGHT));
  PNGWriter ppm_writer2 = PNGWriter(canvas2);
  ppm_writer2.WriteFile("chessboard.png");
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  render_chessboard();

  return 0;
}

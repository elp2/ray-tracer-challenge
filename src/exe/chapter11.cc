#include "display/canvas.h"
#include "display/ppm_writer.h"
#include "lights/point_light.h"
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
#include "shapes/plane.h"
#include "shapes/sphere.h"

#include <cassert>
#include <cmath>
#include <iostream>

const int CAMERA_DIMENSION = 500;

Camera get_camera1() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(4.0, 4.0, 2.0);
  Tuple to = Point(0.0, 0.0, 0.0);
  Tuple up = Vector(0.0, 0.0, 1.0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_world1() {
  World w = World();
  w.set_light(new PointLight(Point(6.0, 5.0, 1.0), Color(1.0, 1.0, 1.0)));

  auto p = new Plane();
  p->SetTransform(RotationX(M_PI / 2.0));
  auto stripe1 = new StripedPattern(Color(0, 0, 0), Color(0.5, 0, 0));
  auto stripe2 = new StripedPattern(Color(0, 0, 0), Color(0, 0, 0.5));
  stripe2->set_transform(RotationZ(M_PI / 2.0));
  auto blended = new BlendedPattern(stripe1, stripe2);
  auto pm1 = Material();
  auto perturbed_plane = new PerturbedPattern(blended);
  pm1.set_pattern(perturbed_plane);
  pm1.set_reflective(0.2);
  p->set_material(pm1);
  w.add_object(p);

  auto s1 = new Sphere();
  s1->SetTransform(Translation(0.0, 0.0, 1.0));
  auto m1 = Material();
  m1.set_color(Color(0.9, 0.1, 0.1));
  auto ring_pattern = new RingPattern(Color(1.0, 0.325, 0.286), Color(0.051, 0.596, 0.729));
  ring_pattern->set_transform(Scaling(0.3, 0.3, 0.3));
  auto perturbed_pattern = new PerturbedPattern(ring_pattern);
  m1.set_pattern(perturbed_pattern);
  s1->set_material(m1);
  w.add_object(s1);

  auto s2 = new Sphere();
  s2->SetTransform(Translation(1.5, -1.0, 0.5) * Scaling(0.5, 0.5, 0.5));
  auto m2 = Material();
  m2.set_color(Color(0.1, 0.9, 0.1));
  auto gp = new GradientPattern(Color(1, 0, 0), Color(0, 1, 0));
  m2.set_pattern(gp);
  s2->set_material(m2);
  w.add_object(s2);

  auto s3 = new Sphere();
  s3->SetTransform(Translation(-1.2, 1.3, 0.3) * Scaling(0.3, 0.3, 0.3));
  auto m3 = Material();
  m3.set_color(Color(0.1, 0.1, 0.9));
  s3->set_material(m3);
  w.add_object(s3);

  auto s4 = new Sphere();
  auto m4 = Material();
  m4.set_transparency(0.8);
  m4.set_color(Color(0.3, 0.3, 0.3));
  s4->set_material(m4);
  s4->SetTransform(Translation(3, 2, 1) * Scaling(0.3, 0.3, 0.3));
  w.add_object(s4);

  return w;
}

Camera get_camera2() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(10, 2, 0);
  Tuple to = Point(0.0, 0.0, 0.0);
  Tuple up = Vector(0.0, 1.0, 0.0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

Sphere *CrystalBall() {
  auto sphere = new Sphere();
  auto material = Material();
  material.set_transparency(0.8);
  material.set_refractive_index(REFRACTIVE_INDEX_GLASS);
  material.set_color(Color(0.3, 0.3, 0.3));
  material.set_reflective(0.2);
  sphere->set_material(material);
  return sphere;
}

World get_world2() {
  World w = World();
  w.set_light(new PointLight(Point(-1, 10.0, 0), Color(1.0, 0.2, 0.2)));

  auto p = new Plane();
  auto pm = Material();
  pm.set_reflective(0.0);
  pm.set_color(Color(0.3, 0, 0));
  w.add_object(p);

  for (int x = -1; x < 2; x += 2) {
    for (int y = 1; y < 4; y += 2) {
      for (int z = -1; z < 2; z += 2) {
        Sphere *sphere = CrystalBall();
        sphere->SetTransform(Translation(x, y, z));
        auto material = Material();
        material.set_transparency(0.2 * y);
        material.set_color(Color(0.3 * y, 0.3 * y, 0.3));
        sphere->set_material(material);

        w.add_object(sphere);
      }
    }
  }

  return w;
}

Camera get_camera3() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(10, 1, 0);
  Tuple to = Point(0.0, 0.0, 0.0);
  Tuple up = Vector(0.0, 1.0, 0.0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_world3() {
  World w = World();
  w.set_light(new PointLight(Point(-1, 20.0, 0), WhiteColor() * 1));

  auto p = new Plane();
  auto pm1 = Material();
  auto grid = new ThreeDPattern(WhiteColor(), BlackColor());
  pm1.set_pattern(grid);
  // When the background is too reflective, it means more reflected light
  // off of the spheres, making them seem weird.
  pm1.set_reflective(0.00);
  pm1.set_shininess(30);
  p->set_material(pm1);
  w.add_object(p);

  auto back_wall = new Plane();
  back_wall->set_material(pm1);
  back_wall->SetTransform(Translation(-3, 0, 0) *  RotationZ(M_PI / 2.0));
  w.add_object(back_wall);

  Sphere *sphere = CrystalBall();
  sphere->SetTransform(Translation(3, 1, 0) * Scaling(1, 1, 1));
  w.add_object(sphere);

  Sphere *red = new Sphere();
  red->SetTransform(Translation(-1.5, 1, 1));
  Material redm = Material();
  redm.set_color(Color(1, 0, 0));
  red->set_material(redm);
  w.add_object(red);

  return w;
}

Camera get_camera4() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 4.0);
  Tuple from = Point(10, 3, 0);
  Tuple to = Point(0.0, 0.0, 0.0);
  Tuple up = Vector(0.0, 1.0, 0.0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

World get_world4(bool add_water) {
  World w = World();
  w.set_light(new PointLight(Point(6, 20.0, 0), WhiteColor() * 1));

  auto p = new Plane();
  auto pm1 = Material();
  auto grid = new ThreeDPattern(WhiteColor(), BlackColor());
  pm1.set_pattern(grid);
  // When the background is too reflective, it means more reflected light
  // off of the spheres, making them seem weird.
  pm1.set_reflective(0.00);
  pm1.set_shininess(30);
  p->set_material(pm1);
  w.add_object(p);

  auto back_wall = new Plane();
  back_wall->set_material(pm1);
  back_wall->SetTransform(Translation(-3, 0, 0) *  RotationZ(M_PI / 2.0));
  w.add_object(back_wall);

  if (add_water) {
    auto water_plane = new Plane();
    auto water_material = Material();
    water_material.set_color(Color(0, 0, 1));
    water_material.set_transparency(0.9);
    water_material.set_reflective(0.3);
    water_material.set_casts_shadow(false);
    water_plane->set_material(water_material);
    water_plane->SetTransform(Translation(0, 3, 0));
    w.add_object(water_plane);
  }

  Sphere *sphere = CrystalBall();
  sphere->SetTransform(Translation(3, 1, 0));
  w.add_object(sphere);

  Sphere *red = new Sphere();
  red->SetTransform(Translation(-1.5, 1, 1));
  Material redm = Material();
  redm.set_color(Color(1, 0, 0));
  red->set_material(redm);
  w.add_object(red);

  return w;
}

World get_world5() {
  World w = World();
  w.set_light(new PointLight(Point(6, 20.0, 0), WhiteColor() * 1));

  auto p = new Plane();
  auto grid = new ThreeDPattern(WhiteColor(), BlackColor());
  auto pm1 = Material();
  pm1.set_pattern(grid);
  pm1.set_reflective(0.00);
  pm1.set_shininess(30);
  p->set_material(pm1);
  w.add_object(p);

  Sphere *near = new Sphere();
  auto nearm = Material();
  nearm.set_color(Color(ElectricBlueColor()));
  near->set_material(nearm);
  near->SetTransform(Translation(5, 1, 0));
  w.add_object(near);

  Sphere *far = new Sphere();
  far->SetTransform(Translation(2, 2, 1));
  Material farm = Material();
  farm.set_color(Color(1, 0, 0));
  far->set_material(farm);
  w.add_object(far);

  Sphere *distant = new Sphere();
  distant->SetTransform(Translation(-3, 2, 0));
  Material distantm = Material();
  distantm.set_color(YellowColor());
  distant->set_material(distantm);
  w.add_object(distant);

  return w;
}

Camera get_camera5() {
  Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 2.0, 0.05, 4, 100);
  // Camera c = Camera(CAMERA_DIMENSION, CAMERA_DIMENSION, M_PI / 2.0, 0, 3, 1);

  Tuple from = Point(10, 3, 0);
  Tuple to = Point(0.0, 0.0, 0.0);
  Tuple up = Vector(0.0, 1.0, 0.0);
  c.set_transform(ViewTransformation(from, to, up));
  return c;
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  // std::cout << "Rendering chapter11_1.ppm." << std::endl;
  // auto canvas1 = get_camera1().Render(get_world1());
  // PPMWriter ppm_writer1 = PPMWriter(canvas1);
  // ppm_writer1.WriteFile("chapter11_1.ppm");

  // std::cout << "Rendering chapter11_2.ppm." << std::endl;
  // auto canvas2 = get_camera2().Render(get_world2());
  // PPMWriter ppm_writer2 = PPMWriter(canvas2);
  // ppm_writer2.WriteFile("chapter11_2.ppm");

  // std::cout << "Rendering chapter11_3.ppm." << std::endl;
  // auto canvas3 = get_camera3().Render(get_world3());
  // PPMWriter ppm_writer3 = PPMWriter(canvas3);
  // ppm_writer3.WriteFile("chapter11_3.ppm");

  // std::cout << "Rendering chapter11_4.ppm." << std::endl;
  // auto canvas4 = get_camera4().Render(get_world4(true));
  // PPMWriter ppm_writer4 = PPMWriter(canvas4);
  // ppm_writer4.WriteFile("chapter11_4.ppm");

  std::cout << "Rendering chapter11_5.ppm." << std::endl;
  auto canvas4 = get_camera5().Render(get_world5());
  PPMWriter ppm_writer4 = PPMWriter(canvas4);
  ppm_writer4.WriteFile("chapter11_5.ppm");


  return 0;
}

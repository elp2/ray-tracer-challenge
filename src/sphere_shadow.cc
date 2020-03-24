#include "display/canvas.h"
#include "display/ppm_writer.h"
#include "primitives/matrix.h"
#include "primitives/transformation.h"
#include "primitives/tuple.h"
#include "shapes/sphere.h"

#include <cmath>
#include <iostream>

const float SPHERE_PADDING = 20.0;
const float SPHERE_RADIUS = 100.0;
const int CANVAS_DIMENSION = 2 * SPHERE_PADDING + 2 * SPHERE_RADIUS;
const int INSET = CANVAS_DIMENSION / 2;

void DrawPixel(Canvas *canvas, int x, int y) {
  x += INSET;
  y += INSET;
  std::cout << x << ", " << y << std::endl;
  canvas->WritePixel(Color(1, 0, 0), x, y);
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  Canvas *canvas = new Canvas(CANVAS_DIMENSION, CANVAS_DIMENSION);

  Sphere s = Sphere();
  Matrix transform = Scaling(SPHERE_RADIUS, SPHERE_RADIUS, SPHERE_RADIUS)
    * Translation(0, 0, SPHERE_RADIUS * 2 + SPHERE_PADDING);
  s.SetTransform(transform);

  for (int y = -INSET; y < INSET; ++y) {
    for (int x = -INSET; x < INSET; ++x) {
      Ray r = Ray(TupleFromPoint(x, y, SPHERE_RADIUS * 2), TupleFromVector(0, 0, -1));
      Intersections xs = s.Intersect(r);
      if (xs.Size()) {
        DrawPixel(canvas, x, y);
      }
    }
  }


  PPMWriter ppm_writer = PPMWriter(canvas);
  ppm_writer.WriteFile("sphere_shadow.ppm");

  return 0;
}

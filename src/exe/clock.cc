#include "primitives/tuple.h"
#include "display/canvas.h"
#include "primitives/matrix.h"
#include "primitives/transformation.h"
#include "images/ppm_writer.h"

#include <cmath>
#include <iostream>

const float LINE_LENGTH = 20.0;
const float LINE_INSET = 200.0;
const int CANVAS_DIMENSION = 2 * LINE_INSET + 4 * LINE_LENGTH;
const int INSET = CANVAS_DIMENSION / 2;

void DrawPixel(Canvas *canvas, Tuple p) {
  int x = floor(p.x()) + INSET;
  int y = floor(p.y()) + INSET;
  std::cout << x << ", " << y << std::endl;
  canvas->WritePixel(Color(1, 0, 0), x, y);
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  Canvas *canvas = new Canvas(CANVAS_DIMENSION, CANVAS_DIMENSION);

  Tuple line_start = Point(0.0, LINE_INSET, 0.0);
  Tuple line_end = Point(0.0, LINE_INSET + LINE_LENGTH, 0.0);

  Matrix tick_rotation = RotationZ(2.0 * M_PI / 12.0);
  for (int hour = 0; hour < 12; ++hour) {
    Tuple line_slope = Scaling(1.0 / LINE_LENGTH, 1.0 / LINE_LENGTH, 1.0 / LINE_LENGTH) 
      * (line_end - line_start);
    Tuple point = line_start;
    for (int pixel = 0; pixel < LINE_LENGTH; ++pixel) {
      DrawPixel(canvas, point);
      point = point + line_slope;
    }

    line_start = tick_rotation * line_start;
    line_end = tick_rotation * line_end; 
  }

  PPMWriter ppm_writer = PPMWriter(canvas);
  ppm_writer.WriteFile("clock.ppm");

  return 0;
}

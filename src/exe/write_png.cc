#include "primitives/tuple.h"
#include "display/canvas.h"
#include "primitives/matrix.h"
#include "primitives/transformation.h"
#include "images/png_writer.h"

#include <cmath>
#include <iostream>

const float LINE_LENGTH = 20.0;
const float LINE_INSET = 200.0;
const int CANVAS_DIMENSION = 2 * LINE_INSET + 4 * LINE_LENGTH;
const int INSET = CANVAS_DIMENSION / 2;

void DrawPixel(Canvas *canvas, Tuple p) {
  int x = floor(p.x()) + INSET;
  int y = floor(p.y()) + INSET;
  canvas->WritePixel(Color(1, 0, 0), x, y);
}

void DrawClock() {
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

  PNGWriter png_writer = PNGWriter(canvas);
  png_writer.WriteFile("clock.png");
}

void DrawGradient() {
  const int DIMENSION = 100;
  Canvas *canvas = new Canvas(DIMENSION, DIMENSION);
  for (int y = 0; y < DIMENSION; ++y) {
    for (int x = 0; x < DIMENSION; ++x) {
      canvas->WritePixel(Color((float)y / DIMENSION, 0, (float)x / DIMENSION), x, y);
    }
  }
  PNGWriter png_writer = PNGWriter(canvas);
  png_writer.WriteFile("gradient.png");
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  DrawGradient();
  DrawClock();

  return 0;
}

#include "primitives/tuple.h"
#include "display/canvas.h"
#include "images/ppm_writer.h"

#include <cmath>

const int CANVAS_WIDTH = 900;
const int CANVAS_HEIGHT = 550;

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  auto pos = Vector(0, 1, 0);
  auto vel = Vector(0.1, 1.8, 0).Normalized();
  vel = vel * 11.25;
  const auto wind = Vector(-0.01, 0, 0);
  const auto gravity = Vector(0, -0.1, 0);

  Canvas *canvas = new Canvas(CANVAS_WIDTH, CANVAS_HEIGHT);

  while (pos.y() >= 0) {
    int y = ceil(pos.y() - CANVAS_HEIGHT);
    int x = pos.x();
    if (y >= 0 && y < CANVAS_HEIGHT && x >= 0 && x < CANVAS_WIDTH) {
      canvas->WritePixel(Color(1, 0, 0), x, y);
    }
    pos = pos + vel;
    vel = vel + gravity + wind;
    pos.Debug();

  }

  PPMWriter ppm_writer = PPMWriter(canvas);
  ppm_writer.WriteFile("particle.ppm");

  return 0;
}

#include "primitives/tuple.h"

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  auto pos = TupleFromVector(0, 1, 0);
  auto vel = TupleFromVector(0.1, 1, 0).Normalized();
  const auto wind = TupleFromVector(-0.01, 0, 0);
  const auto gravity = TupleFromVector(0, -0.1, 0);

  while (pos.y() >= 0) {
    pos = pos + vel;
    vel = vel + gravity + wind;
    pos.Debug();
  }

  return 0;
}

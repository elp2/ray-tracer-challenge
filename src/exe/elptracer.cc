#include "gui/gui.h"

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  auto gui = new Gui();
  gui->Show();

  return 0;
}

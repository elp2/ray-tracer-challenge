#ifndef RTC_GUI_GUI_H
#define RTC_GUI_GUI_H

#include <vector>
#include "SDL.h"

class Gui {
 public:
  Gui();
  ~Gui() = default;

  void Show();

 private:
  void Cleanup() const;
  bool EventLoop();
  void Frame();

  SDL_GLContext context_;
  SDL_Window *window_;
};

#endif    // RTC_GUI_GUI_H

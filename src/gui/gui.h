#ifndef RTC_GUI_GUI_H
#define RTC_GUI_GUI_H

#include <vector>

class Gui {
 public:
  Gui();
  ~Gui() = default;

  void Show() const;

 private:
  void Cleanup() const;
};

#endif    // RTC_GUI_GUI_H

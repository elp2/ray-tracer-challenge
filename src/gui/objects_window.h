#ifndef RTC_GUI_OBJECTS_WINDOW_H
#define RTC_GUI_OBJECTS_WINDOW_H

#include <vector>

class ObjectView;
class Shape;

class ObjectsWindow {
 public:
  ObjectsWindow();
  ~ObjectsWindow() = default;

  // Returns whether the widgets changed this frame.
  bool Frame();

  // Return objects contained in the window.
  std::vector<Shape *> GetObjects();

 private:
  ObjectView *object_view_;
};

#endif    // RTC_GUI_OBJECTS_WINDOW_H

#ifndef RTC_GUI_ITEM_LIST_H
#define RTC_GUI_ITEM_LIST_H

#include <vector>

class Shape;
class ObjectView;

class ItemList {
 public:
  ItemList();
  ~ItemList() = default;

  // Returns whether the widgets changed this frame.
  bool Frame();

  std::vector<Shape *> Items();

 private:
  std::vector<ObjectView *> items_;
};

#endif    // RTC_GUI_ITEM_LIST_H

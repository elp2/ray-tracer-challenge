#include "gui/item_list.h"

#include "imgui.h"

#include "gui/object_view.h"

ItemList::ItemList() {
}

bool ItemList::Frame() {
  bool updated = false;

  int id = 0;
  for (auto i : items_) {
    ImGui::PushID(++id);
    updated |= i->Frame();
    ImGui::PopID();
  }

  if (ImGui::Button("Add Object")) {
    items_.push_back(new ObjectView());
  }

  return updated;
}

std::vector<Shape *> ItemList::Items() {
  std::vector<Shape *> ret;
  for (auto i : items_) {
    auto shape = i->GetShape();
    if (shape) {
      ret.push_back(shape);
    }
  }
  return ret;
}

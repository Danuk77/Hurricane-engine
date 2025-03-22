#pragma once

#include <memory>
#include <vector>

#include "game_objects/box.hpp"

class Scene {
public:
  Scene() {}
  void render();
  void add_box(std::unique_ptr<Box>);
  std::vector<std::unique_ptr<Box>> game_objects;
};

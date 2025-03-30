#pragma once

#include <memory>
#include <vector>

#include "game_objects/box.hpp"
#include "game_objects/circle.hpp"

class Scene {
public:
  Scene() {}
  virtual void render();
  void add_box(std::unique_ptr<Box>);
  void add_circle(std::unique_ptr<Circle>);
  std::vector<std::unique_ptr<Box>> game_objects;
  std::vector<std::unique_ptr<Circle>> circles;
};

#pragma once

#include <memory>
#include <vector>

#include "game_objects/box.hpp"
#include "game_objects/circle.hpp"
#include "game_objects/gameobject.hpp"

class Scene {
public:
  Scene() {}
  std::vector<std::unique_ptr<GameObject>> game_objects;

  virtual void render();
  void add_gameobject(std::unique_ptr<GameObject> game_object);
};

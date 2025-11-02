#pragma once

#include <memory>
#include <vector>

#include "game_objects/gameobject.hpp"
#include "rendering/screen.hpp"

class Scene {
public:
  Scene(): window(create_window()) {}
  std::vector<std::unique_ptr<GameObject>> game_objects;

  virtual void render();
  void add_gameobject(std::unique_ptr<GameObject> game_object);

private:
  GLFWwindow *window;
  void draw_scene();
};

#pragma once

#include <memory>
#include <vector>

#include "game_objects/gameobject.hpp"
#include "rendering/screen.hpp"

class Scene
{
public:
  Scene()
    : window(create_window())
  {
  }

  virtual void render();
  void add_gameobject(std::unique_ptr<GameObject> game_object);
  GLFWwindow* get_window() { return window; };
  const std::vector<std::unique_ptr<GameObject>>& get_gameobjects();

private:
  GLFWwindow* window;
  std::vector<std::unique_ptr<GameObject>> game_objects;

  void draw_scene();
  void execute_components();
};

#pragma once

#include "game_objects/gameobject.hpp"
#include "input/input.hpp"
#include "physics/particle.hpp"
#include <vector>
class CharacterController : public Component
{
public:
  CharacterController(GLFWwindow* window, Particle* particle)
    : window(window)
    , particle(particle)
  {
  }
  void execute_component();

private:
  GLFWwindow* window;
  Particle* particle;

  void handle_user_input(std::vector<Input> user_input);
  void move(Input direction);
  void move_left();
  void move_right();
  void jump();
};

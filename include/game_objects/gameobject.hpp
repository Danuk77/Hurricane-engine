#pragma once

#include <vector>

#include "input/input.hpp"
#include "physics/colliders/collider.hpp"

class GameObject {
public:
  virtual void render() = 0;
  virtual void handle_user_input(std::vector<Input> user_input) = 0;
  virtual Collider &get_collider() = 0;
};

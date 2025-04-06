#pragma once

#include <vector>

#include "input/input.hpp"

class GameObject {
public:
  virtual void render() = 0;
  virtual void handle_user_input(std::vector<Input> user_input) = 0;
};

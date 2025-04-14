#pragma once

#include <vector>

#include "glm/ext/vector_float3.hpp"
#include "input/input.hpp"
#include "physics/colliders/collider.hpp"

// TODO: Move particle into this class
class GameObject {
public:
  glm::vec3 sprite_color = glm::vec3(0, 1, 0);
  virtual void render() = 0;
  virtual void handle_user_input(std::vector<Input> user_input) = 0;
  virtual Collider &get_collider() = 0;
  virtual void apply_forces() = 0;
};

#pragma once
#include "../glm/ext/vector_float2.hpp"

class Collision {
public:
  Collision(glm::vec2 collision_depth, glm::vec2 collision_normal)
      : collision_depth(collision_depth), collision_normal(collision_normal) {}
  glm::vec2 collision_depth, collision_normal;
};

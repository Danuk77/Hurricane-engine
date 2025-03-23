#pragma once
#include "../glm/ext/vector_float2.hpp"

class Collision {
public:
  Collision(float collision_depth, glm::vec2 collision_normal)
      : collision_depth(collision_depth), collision_normal(collision_normal) {}
  glm::vec2 collision_normal;
  float collision_depth;
};

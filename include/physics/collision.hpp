#pragma once
#include <array>
#include <memory>

#include "../glm/ext/vector_float2.hpp"
#include "physics/particle.hpp"

class Collision {
public:
  Collision(float collision_depth, glm::vec2 collision_normal,
            std::array<std::shared_ptr<Particle>, 2> particles)
      : collision_depth(collision_depth), collision_normal(collision_normal),
        particles(particles) {}
  std::array<std::shared_ptr<Particle>, 2> particles;
  glm::vec2 collision_normal;
  float collision_depth;
};

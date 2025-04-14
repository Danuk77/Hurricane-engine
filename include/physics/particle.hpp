#pragma once

#include <memory>

#include "./transform.hpp"

class Particle {
public:
  Particle(std::shared_ptr<Transform> transform, float mass);
  void apply_force(glm::vec2 force);
  void execute_physics_tick(float duration_from_last_tick);

private:
  std::shared_ptr<Transform> transform;

  glm::vec2 velocity;
  glm::vec2 acceleration;
  glm::vec2 accumulated_force;
  float inverse_mass;
  float damping_factor;

  void clear_accumulated_force();
};

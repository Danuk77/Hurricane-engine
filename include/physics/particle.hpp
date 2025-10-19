#pragma once

#include <memory>

#include "./transform.hpp"

class Particle {
public:
  Particle(std::shared_ptr<Transform> transform, float inverse_mass);
  // NOTE: This constructor is for an immovable object (with inifinite mass of 0)
  Particle(std::shared_ptr<Transform> transform);
  float inverse_mass;

  void apply_force(glm::vec2 force);
  void apply_impulse(glm::vec2 impulse);
  void execute_physics_tick(float duration_from_last_tick);
  glm::vec2 get_velocity();
  void clear_velocity();
  std::shared_ptr<Transform> transform;

private:

  glm::vec2 velocity = glm::vec2(0);
  glm::vec2 acceleration = glm::vec2(0);
  glm::vec2 accumulated_force = glm::vec2(0);
  float damping_factor;

  void clear_accumulated_force();
};

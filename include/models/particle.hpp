#pragma once
#include "glm/ext/vector_float3.hpp"

/**
 * Simplest physics object in the engine.
 */
class Particle {
public:
  Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration,
           float damping, float mass);
  glm::vec3 position;
  glm::vec3 velocity;
  glm::vec3 acceleration;
  float damping_factor;

  glm::vec3 force_accumulated;

  // void set_position(glm::vec3 position);
  // void set_velocity(glm::vec3 velocity);
  // void set_acceleration(glm::vec3 acceleration);
  // void set_damping_factor(float damping_factor);

  // Integrate GLFW and use its timer in the engine
  void integrate(float time_duration);

private:
protected:
  float inverse_mass;
};

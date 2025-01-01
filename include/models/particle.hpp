#pragma once
#include "glm/ext/vector_float3.hpp"
#include "glm/glm.hpp"

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
  float mass;
  float damping_factor;
  float inverse_mass;

  glm::vec3 force_accumulated;

  // Integrate GLFW and use its timer in the engine
  void integrate(float time_duration);
  void add_force(glm::vec3 force);
  bool has_inifinite_mass();

private:
  void clear_accumulated_force();
};

#pragma once

#include "glm/ext/vector_float3.hpp"
#include "models/particle.hpp"
class Collision {
public:
  /**
  * The particles colliding with each other
  * If a particle is an immovable scenary object, it will be nullptr
  */
  Particle *colliding_particles[2];
  float coefficient_of_restitution;
  float collision_penetration;
  glm::vec3 contact_normal;

  void resolve_collision(float duration) const;
  void resolve_penetration(float duration) const;
private:
  float calculate_separating_velocity() const;
  float adjust_for_resting_contact(float separating_velocity, float duration) const;
  float calculate_total_inverse_mass() const;

  glm::vec3 calculate_impulse_per_unit_inverse_mass(float total_inverse_mass, float change_in_separating_velocity) const;
  void apply_impulse(glm::vec3 impulse_per_unit_inverse_mass) const;
  void unpenetrate_particles(glm::vec3 penetration_resolution_per_unit_inverse_mass) const;
  
};

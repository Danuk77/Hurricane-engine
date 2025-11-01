#include "physics/force_generators/gravity.hpp"

std::vector<Particle*> GravityForceGenerator::subscribed_particles;

const float GRAVITY_STRENGTH = 1000;

void
GravityForceGenerator::apply_forces()
{
  for (auto* particle : subscribed_particles) {
    float gravity_force = GRAVITY_STRENGTH / (particle)->inverse_mass;
    (particle)->apply_force(glm::vec2(0, gravity_force));
  }
};

#include "models/particle.hpp"
#include "glm/ext/vector_float3.hpp"
#include <cassert>
#include <stdexcept>

Particle::Particle(glm::vec3 position, glm::vec3 velocity,
                   glm::vec3 acceleration, float damping_factor, float mass)
    : position(position), acceleration(acceleration), velocity(velocity),
      damping_factor(damping_factor) {
  if (mass <= 0 || mass >= 1) {
    throw std::runtime_error(
        "Damping factor must be greater than 0 and less than 1");
  }

  inverse_mass = 1 / mass;
};

void Particle::integrate(float time_duration) {
  assert(time_duration > 0);

  // S = ut + 1/2at*2
  position += (velocity * time_duration) +
              (glm::vec3(0.5) * acceleration * time_duration * time_duration);
  glm::vec3 resultant_acceleration = force_accumulated * inverse_mass;
  velocity += resultant_acceleration * time_duration;
  velocity *= pow(damping_factor, time_duration);
}

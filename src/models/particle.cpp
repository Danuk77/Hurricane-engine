#include "models/particle.hpp"
#include <stdexcept>

Particle::Particle(glm::vec3 position, glm::vec3 velocity,
                   glm::vec3 acceleration, float damping_factor, float mass)
    : position(position), acceleration(acceleration), velocity(velocity),
      damping_factor(damping_factor){
  if(mass<=0 || mass >= 1){
    throw std::runtime_error("Damping factor must be greater than 0 and less than 1");
  }

  inverse_mass = 1 / mass;
};

void Particle::integrate(float time){
  
}

#include "physics/particle.hpp"
#include "glm/exponential.hpp"

Particle::Particle(std::shared_ptr<Transform> transform, float inverse_mass)
  : transform(transform)
  , inverse_mass(inverse_mass)
{
  velocity = glm::vec2(0);
  acceleration = glm::vec2(0);
  accumulated_force = glm::vec2(0);
  damping_factor = 0.95f;
}

void
Particle::apply_force(glm::vec2 force)
{
  accumulated_force += force;
}

void
Particle::clear_accumulated_force()
{
  accumulated_force = glm::vec2(0);
}

void
Particle::execute_physics_tick(float duration_from_last_tick)
{
  transform->position =
    transform->position + (velocity * duration_from_last_tick);
  acceleration = inverse_mass * accumulated_force;
  velocity = (velocity * glm::pow(damping_factor, duration_from_last_tick)) +
             (acceleration * duration_from_last_tick);

  // if(accumulated_force == glm::vec2(0) && velocity != glm::vec2(0)){
  //   velocity = glm::vec2(velocity.x/2, velocity.y/2);
  // }

  clear_accumulated_force();
}

glm::vec2
Particle::get_velocity()
{
  return velocity;
}

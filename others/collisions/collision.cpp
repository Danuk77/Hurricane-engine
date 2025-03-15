#include "models/collisions/collision.hpp"
#include "glm/geometric.hpp"
// TODO: There is a chance that the first particle is null in which case this whole logic fails.
// Write logic to solve this scenario

void Collision::resolve_collision(float duration) const{
  float separating_velocity = calculate_separating_velocity();

  // Check if the particles are moving apart (if they are they will not collide)
  if (separating_velocity > 0)
    return;

  float new_separating_velocity =
      -coefficient_of_restitution * separating_velocity;

  new_separating_velocity = adjust_for_resting_contact(new_separating_velocity, duration); 

  float change_in_separating_velocity =
      new_separating_velocity - separating_velocity;

  float total_inverse_mass = calculate_total_inverse_mass();

  // Check if both the particles are immovable
  if(total_inverse_mass <= 0) return;

  glm::vec3 impulse_per_unit_inverse_mass = calculate_impulse_per_unit_inverse_mass(total_inverse_mass, change_in_separating_velocity);
  apply_impulse(impulse_per_unit_inverse_mass);
}

float Collision::calculate_separating_velocity() const {
  glm::vec3 particle_one_velocity = colliding_particles[0]->velocity;
  glm::vec3 particle_two_velocity(0);

  if (colliding_particles[1])
    particle_two_velocity = colliding_particles[1]->velocity;

  glm::vec3 relative_velocity = particle_one_velocity - particle_two_velocity;
  return glm::dot(relative_velocity, contact_normal);
}

float Collision::adjust_for_resting_contact(float separating_velocity, float duration) const {
  glm::vec3 relative_acceleration = colliding_particles[0]->acceleration;
  if(colliding_particles[1]){
    relative_acceleration -= colliding_particles[1]->acceleration;
  }
  glm::vec3 relative_velocity = relative_acceleration * duration;
  float relative_separating_velocity_projected_to_contact_normal = glm::dot(relative_velocity, contact_normal);
  
  if(relative_separating_velocity_projected_to_contact_normal < 0){
    separating_velocity += coefficient_of_restitution * relative_separating_velocity_projected_to_contact_normal;

    if(separating_velocity == 0) return 0;
  }

  return separating_velocity;
}

float Collision::calculate_total_inverse_mass() const {
  if (colliding_particles[1])
    return colliding_particles[1]->inverse_mass +
           colliding_particles[0]->inverse_mass;
  return colliding_particles[0]->inverse_mass;
}

glm::vec3 Collision::calculate_impulse_per_unit_inverse_mass(float total_inverse_mass, float change_in_separating_velocity) const{
  float impulse_per_unit_inverse_mass = change_in_separating_velocity / total_inverse_mass;
  glm::vec3 impulse_in_contact_normal_direction = impulse_per_unit_inverse_mass * contact_normal;

  return impulse_in_contact_normal_direction;
}

void Collision::apply_impulse(glm::vec3 impulse_per_unit_inverse_mass) const{
  colliding_particles[0]->velocity = (colliding_particles[0]->inverse_mass * impulse_per_unit_inverse_mass) + colliding_particles[0]->velocity;

  if(colliding_particles[1]){
    // The second object must travel in the opposite direction
    colliding_particles[1]->velocity = -(colliding_particles[1]->inverse_mass * impulse_per_unit_inverse_mass) + colliding_particles[1]->velocity;
  }
}

void Collision::resolve_penetration(float duration) const{
  if(collision_penetration <= 0) return;

  float total_inverse_mass = calculate_total_inverse_mass();
  if(total_inverse_mass <= 0) return;

  glm::vec3 penetration_resolution_per_unit_inverse_mass = contact_normal * -(collision_penetration / total_inverse_mass);

  unpenetrate_particles(penetration_resolution_per_unit_inverse_mass);
}

void Collision::unpenetrate_particles(glm::vec3 penetration_resolution_per_unit_inverse_mass) const{
  colliding_particles[0]->position = (colliding_particles[0]->position + (penetration_resolution_per_unit_inverse_mass * colliding_particles[0]->mass));

  if(colliding_particles[1]){
    // TODO: the text book hasnt got the negative sign, maybe we need to also get rid of it?
    // The second object must be resolved in the opposite direction
    colliding_particles[1]->position = (colliding_particles[0]->position - (penetration_resolution_per_unit_inverse_mass * colliding_particles[0]->mass));
  }
}

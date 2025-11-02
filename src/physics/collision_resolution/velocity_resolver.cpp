#include <iostream>
#include "data_structures/priority_queue.hpp"
#include "physics/collision_resolution/particle_contact_resolver.hpp"

void
resolve(SeparatingVelocityContact contact);

void
ParticleContactResolver::resolve_velocity(
  const std::vector<std::unique_ptr<Contact>>& contacts,
  int max_iterations)
{
  PriorityQueue<SeparatingVelocityContact>
    contacts_ordered_by_separating_velocity;

  for (auto& contact : contacts) {
    contacts_ordered_by_separating_velocity.insert(
      SeparatingVelocityContact{ &contact });
  }

  while (!contacts_ordered_by_separating_velocity.is_empty()) {
    resolve(contacts_ordered_by_separating_velocity.pop());
  }
}

// TODO: coefficient_of_restitution needs to be hardcoded elsewhere for each
// pair of materials
void
resolve(SeparatingVelocityContact contact)
{
  float coefficient_of_restitution = .1;
  glm::vec2 contact_normal = (*contact.contact)->contact_normal;
  float total_inverse_mass =
    (*contact.contact)->particles_in_contact.at(0)->inverse_mass +
    (*contact.contact)->particles_in_contact.at(1)->inverse_mass;
  float separating_velocity_in_contact_normal =
    (*contact.contact)->separating_velocity;

  if (separating_velocity_in_contact_normal > 0 || total_inverse_mass < 0) {
    return;
  }

  float new_separating_velocity_in_contact_normal =
    -(1 + coefficient_of_restitution) * separating_velocity_in_contact_normal;
  float impulse_to_apply =
    new_separating_velocity_in_contact_normal / total_inverse_mass;

  glm::vec2 impulse_to_apply_to_first_object =
    impulse_to_apply * -contact_normal;
  glm::vec2 impulse_to_apply_to_second_object =
    impulse_to_apply * contact_normal;

  (*contact.contact)
    ->particles_in_contact.at(0)
    ->apply_impulse(impulse_to_apply_to_first_object);

  (*contact.contact)
    ->particles_in_contact.at(1)
    ->apply_impulse(impulse_to_apply_to_second_object);
};

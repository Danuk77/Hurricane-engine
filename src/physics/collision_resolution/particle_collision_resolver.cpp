#include <iostream>
#include <memory>
#include <vector>

#include "data_structures/priority_queue.hpp"
#include "physics/collision_resolution/particle_contact_resolver.hpp"

void
ParticleContactResolver::resolve_contacts(
  const std::vector<std::unique_ptr<Contact>>& contacts,
  int max_iterations)
{

  resolve_velocity(contacts, max_iterations);
  resolve_interpenetration(contacts, max_iterations);
}

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
// TODO: Rename
void
ParticleContactResolver::resolve(SeparatingVelocityContact contact)
{
  float coefficient_of_restitution = .2;
  glm::vec2 contact_normal = (*contact.contact)->contact_normal;
  float total_inverse_mass =
    (*contact.contact)->particles_in_contact.at(0)->inverse_mass +
    (*contact.contact)->particles_in_contact.at(1)->inverse_mass;
  float separating_velocity_in_contact_normal =
    (*contact.contact)->separating_velocity;

  // TODO: This may be the other way around
  if (separating_velocity_in_contact_normal > 0 || total_inverse_mass < 0) {
    return;
  }

  float new_separating_velocity_in_contact_normal =
    (coefficient_of_restitution * separating_velocity_in_contact_normal);
  float difference_in_separating_velocity_in_contact_normal =
    separating_velocity_in_contact_normal -
    new_separating_velocity_in_contact_normal;
  float impules_to_apply_per_unit_mass_in_contact_normal =
    difference_in_separating_velocity_in_contact_normal * total_inverse_mass;

  float impulse_to_apply_for_first_object_in_contact_normal =
    (*contact.contact)->particles_in_contact.at(0)->inverse_mass *
    impules_to_apply_per_unit_mass_in_contact_normal;
  float impulse_to_apply_for_second_object_in_contact_normal =
    (*contact.contact)->particles_in_contact.at(1)->inverse_mass *
    impules_to_apply_per_unit_mass_in_contact_normal;

  (*contact.contact)
    ->particles_in_contact.at(0)
    ->apply_impulse(impulse_to_apply_for_first_object_in_contact_normal *
                    contact_normal);

  (*contact.contact)
    ->particles_in_contact.at(1)
    ->apply_impulse(impulse_to_apply_for_second_object_in_contact_normal *
                    -contact_normal);
};

void
ParticleContactResolver::resolve_interpenetration(
  const std::vector<std::unique_ptr<Contact>>& contacts,
  int max_iterations)
{
}

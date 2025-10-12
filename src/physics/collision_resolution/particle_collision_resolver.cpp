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
  float coefficient_of_restitution = 1;
  glm::vec2 contact_normal = (*contact.contact)->contact_normal;
  float total_inverse_mass =
    (*contact.contact)->particles_in_contact.at(0)->inverse_mass +
    (*contact.contact)->particles_in_contact.at(1)->inverse_mass;
  float separating_velocity_in_contact_normal =
    (*contact.contact)->separating_velocity;

  // TODO: (BUG) One item might have a mass and hence it should be moved
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

void
ParticleContactResolver::resolve_interpenetration(
  const std::vector<std::unique_ptr<Contact>>& contacts,
  int max_iterations)
{
  PriorityQueue<InterpenetrationContact> contacts_ordered_by_interpenetration;

  for (auto& contact : contacts) {
    contacts_ordered_by_interpenetration.insert(
      InterpenetrationContact{ &contact });
  }

  while (!contacts_ordered_by_interpenetration.is_empty()) {
    reolve_penetration(contacts_ordered_by_interpenetration.pop());
  }
}

void
ParticleContactResolver::reolve_penetration(InterpenetrationContact contact)
{
  float contact_depth = (*contact.contact)->contact_depth;
  glm::vec2 contact_normal = (*contact.contact)->contact_normal;

  // TODO: Infinite mass objects are immovable
  if (contact_depth <= 0) {
    return;
  }

  float total_inverse_mass =
    (*contact.contact)->particles_in_contact.at(0)->inverse_mass +
    (*contact.contact)->particles_in_contact.at(1)->inverse_mass;

  glm::vec2 penetration_per_unit_mass_in_contact_normal =
    (contact_depth / total_inverse_mass) * contact_normal;

  std::shared_ptr<Particle> particle_one_in_contact =
    (*contact.contact)->particles_in_contact.at(0);

  std::shared_ptr<Particle> particle_two_in_contact =
    (*contact.contact)->particles_in_contact.at(1);

  particle_one_in_contact->transform->position +=
    (particle_one_in_contact->inverse_mass *
     penetration_per_unit_mass_in_contact_normal);

  particle_two_in_contact->transform->position -=
    (particle_two_in_contact->inverse_mass *
     penetration_per_unit_mass_in_contact_normal);
};

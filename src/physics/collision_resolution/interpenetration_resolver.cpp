#include "data_structures/priority_queue.hpp"
#include "physics/collision_resolution/particle_contact_resolver.hpp"

void
resolve(InterpenetrationContact contact);

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
    resolve(contacts_ordered_by_interpenetration.pop());
  }
}

void
resolve(InterpenetrationContact contact)
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

  particle_one_in_contact->transform->position -=
    (particle_one_in_contact->inverse_mass *
     penetration_per_unit_mass_in_contact_normal);

  particle_two_in_contact->transform->position +=
    (particle_two_in_contact->inverse_mass *
     penetration_per_unit_mass_in_contact_normal);
};

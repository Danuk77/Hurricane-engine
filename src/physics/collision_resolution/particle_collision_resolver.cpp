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
  PriorityQueue<Contact>
    contacts_ordered_by_separating_velocity;

  //for (auto& contact : contacts) {
  //  contacts_ordered_by_separating_velocity.insert(contact);
  //}
}
void
ParticleContactResolver::resolve_interpenetration(
  const std::vector<std::unique_ptr<Contact>>& contacts,
  int max_iterations)
{
}

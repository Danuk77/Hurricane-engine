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

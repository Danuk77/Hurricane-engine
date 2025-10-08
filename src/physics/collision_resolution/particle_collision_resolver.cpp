#include <vector>

#include "physics/collision_resolution/particle_contact_resolver.hpp"

void ParticleContactResolver::resolve_contacts(
    std::vector<Contact> contacts, int max_iterations) {
  resolve_velocity(contacts, max_iterations);
  resolve_interpenetration(contacts, max_iterations);
}

void ParticleContactResolver::resolve_velocity(
    std::vector<Contact> contacts, int max_iterations) {}
void ParticleContactResolver::resolve_interpenetration(
    std::vector<Contact> contacts, int max_iterations) {}

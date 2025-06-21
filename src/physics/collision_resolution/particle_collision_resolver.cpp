#include <vector>

#include "physics/collision_resolution/particle_collision_resolver.hpp"

void ParticleCollisionResolver::resolve_collisions(
    std::vector<Collision> collisions, int max_iterations) {
  resolve_velocity(collisions, max_iterations);
  resolve_interpenetration(collisions, max_iterations);
}

void ParticleCollisionResolver::resolve_velocity(
    std::vector<Collision> collisions, int max_iterations) {}
void ParticleCollisionResolver::resolve_interpenetration(
    std::vector<Collision> collisions, int max_iterations) {}

#pragma once

#include "physics/collision_resolution/resolver.hpp"

class ParticleCollisionResolver : public CollisionResolver {
public:
  void resolve_collisions(std::vector<Collision> collisions,
                          int max_iterations) override;

private:
  void resolve_velocity(std::vector<Collision> collisions,
                        int max_iterations) override;
  void resolve_interpenetration(std::vector<Collision> collisions,
                                int max_iterations) override;
};

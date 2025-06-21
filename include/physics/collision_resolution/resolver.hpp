#pragma once

#include <vector>

#include "physics/collision.hpp"

class CollisionResolver {
public:
  virtual void resolve_collisions(std::vector<Collision> collisions,
                                  int max_iterations) = 0;

private:
  virtual void resolve_velocity(std::vector<Collision> collisions,
                                int max_iterations) = 0;
  virtual void resolve_interpenetration(std::vector<Collision> collisions,
                                        int max_iterations) = 0;
};

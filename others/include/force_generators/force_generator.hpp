#pragma once

#include "models/particle.hpp"
class ForceGenerator{
public:
  virtual void generate_force(Particle *particle, float duration) const = 0;
};

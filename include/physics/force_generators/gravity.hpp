#pragma once
#include "physics/force_generators/force_generator.hpp"

class GravityForceGenerator : public ForceGenerator<GravityForceGenerator>
{
  friend class ForceGenerator<GravityForceGenerator>;

public:
  static void apply_forces();

private:
  static std::vector<Particle*> subscribed_particles;
};

#include "models/force_generators/gravity_generator.hpp"

void GravityGenerator::generate_force(Particle *particle, float duration) const{
  if(particle->has_inifinite_mass()) return;

  particle->add_force(gravity * particle->mass);
}

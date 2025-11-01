#include "physics/force_generators/gravity.hpp"

std::vector<Particle*> GravityForceGenerator::subscribed_particles;

void GravityForceGenerator::apply_forces(){
  std::cout << subscribed_particles.size() << std::endl;
};

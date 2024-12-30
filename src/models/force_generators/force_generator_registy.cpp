#include "models/force_generators/force_generator_registry.hpp"
#include <stdexcept>
#include <vector>

void ForceGeneratorRegistry::register_generator(
    Particle *particle, ForceGenerator *force_generator) {
  ParticleForceGeneratorRegistration entry = {particle, force_generator};
  registry.push_back(entry);
}

void ForceGeneratorRegistry::deregister_generator(
    Particle *particle, ForceGenerator *force_generator) {
  std::vector<ParticleForceGeneratorRegistration>::iterator iterator;

  for (iterator = registry.begin(); iterator != registry.end(); iterator++) {
    if (iterator->particle == particle && iterator->force_generator == force_generator) {
      registry.erase(iterator);
      return;
    }
  }

  throw std::runtime_error("Given registration for force generator not found");
}

void ForceGeneratorRegistry::clear_registrations(){
  registry.clear();
}

void ForceGeneratorRegistry::apply_forces(float duration){
  std::vector<ParticleForceGeneratorRegistration>::iterator iterator;

  for (iterator = registry.begin(); iterator != registry.end(); iterator++) {
    iterator->force_generator->generate_force(iterator->particle, duration);
  }
}

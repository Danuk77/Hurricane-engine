#pragma once

#include "models/force_generators/force_generator.hpp"
#include "models/particle.hpp"
#include <vector>

class ForceGeneratorRegistry {
protected:
  struct ParticleForceGeneratorRegistration {
    Particle *particle;
    ForceGenerator *force_generator;
  };
  std::vector<ParticleForceGeneratorRegistration> registry;
public:
  /**
  * Register a force generator with a particle
  * @particle The particle to apply forces to by the generator
  * @force_generator The generator used for generating the force on the particle
  */
  void register_generator(Particle *particle, ForceGenerator *force_generator);

  /**
  * Deregister a force generator with a particle
  * @particle The particle registered
  * @force_generator The generator used for generating the force on the particle
  */
  void deregister_generator(Particle *particle, ForceGenerator *force_generator);

  /**
  * Clear all force generator registrations
  */
  void clear_registrations();

  /**
  * Call all force registers to apply forces on the particles they are registered to apply
  * a force to
  * @duration The duration to apply the force for
  */
  void apply_forces(float duration);
};

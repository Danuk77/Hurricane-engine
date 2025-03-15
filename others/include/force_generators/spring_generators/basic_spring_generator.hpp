#pragma once

#include "models/force_generators/force_generator.hpp"

class BasicSpringGenerator : public ForceGenerator {
private:
  Particle *attached_particle;
  float spring_constant;
  float rest_length;

public:
  BasicSpringGenerator(Particle *attached_particle, float spring_constant,
                       float rest_length)
      : attached_particle(attached_particle), spring_constant(spring_constant),
        rest_length(rest_length){};
  /**
  * Calculate the force applied on the particle by the spring using Hooke's law
  * @param particle The particle to which the force is applied on
  * @param duration The duration in which the force is applied
  */
  void generate_force(Particle *particle, float duration) const override;
};

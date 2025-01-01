#pragma once

#include "models/force_generators/force_generator.hpp"

class AnchoredSpringGenerator : public ForceGenerator {
private:
  glm::vec3 attached_position;
  float spring_constant;
  float rest_length;

public:
  AnchoredSpringGenerator(glm::vec3 attached_position, float spring_constant,
                       float rest_length)
      : attached_position(attached_position), spring_constant(spring_constant),
        rest_length(rest_length){};
  /**
  * Calculate the force applied on the particle by the spring using Hooke's law
  * @param particle The particle to which the force is applied on
  * @param duration The duration in which the force is applied
  */
  void generate_force(Particle *particle, float duration) const override;
};

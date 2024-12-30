#pragma once

#include "glm/ext/vector_float3.hpp"
#include "models/force_generators/force_generator.hpp"

class GravityGenerator : public ForceGenerator {
public:
  glm::vec3 gravity;

  GravityGenerator(const glm::vec3 gravity): gravity(gravity){};
  void generate_force(Particle *particle, float duration) const override;
};

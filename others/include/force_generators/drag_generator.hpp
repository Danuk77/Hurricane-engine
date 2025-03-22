#pragma once

#include "models/force_generators/force_generator.hpp"

class DragGenerator : public ForceGenerator {
private:
  float drag_coefficient_one, drag_coefficient_two;

public:
  DragGenerator(float coefficient_one, float coefficient_two)
      : drag_coefficient_one(coefficient_one),
        drag_coefficient_two(coefficient_two){};
  void generate_force(Particle *particle, float duration) const override;
};

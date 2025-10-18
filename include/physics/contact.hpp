#pragma once
#include <array>
#include <memory>

#include "../glm/ext/vector_float2.hpp"
#include "physics/particle.hpp"

struct Contact {
  float contact_depth;
  glm::vec2 contact_normal;
  std::array<std::shared_ptr<Particle>, 2> particles_in_contact;
  float separating_velocity;
};

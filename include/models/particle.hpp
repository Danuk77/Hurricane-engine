#pragma once
#include "glm/ext/vector_float3.hpp"

/**
  * Simplest physics object in the engine.
  */
class Particle{
  public:
    Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, float damping);
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float damping;
};

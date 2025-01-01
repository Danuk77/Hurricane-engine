#include "models/force_generators/spring_generators/anchored_spring_generator.hpp"

void AnchoredSpringGenerator::generate_force(Particle *particle, float duration) const{
  glm::vec3 elastic_vector = particle->position - attached_position;
  float elasticity_maginitude = elastic_vector.length();
  glm::vec3 elasticity_direction = glm::normalize(elastic_vector);

  glm::vec3 force_applied = -spring_constant * (elasticity_maginitude - rest_length) * elasticity_direction;
} 


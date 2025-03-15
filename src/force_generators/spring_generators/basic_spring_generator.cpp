#include "models/force_generators/spring_generators/basic_spring_generator.hpp"
#include "glm/geometric.hpp"

void BasicSpringGenerator::generate_force(Particle *particle, float duration) const{
  glm::vec3 elastic_vector = particle->position - attached_particle->position;
  float elasticity_maginitude = elastic_vector.length();
  glm::vec3 elasticity_direction = glm::normalize(elastic_vector);

  glm::vec3 force_applied = -spring_constant * (elasticity_maginitude - rest_length) * elasticity_direction;
} 

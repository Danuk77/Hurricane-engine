#include "models/force_generators/spring_generators/elastic_bungee.hpp"
#include "glm/geometric.hpp"

void ElasticBungeeGenerator::generate_force(Particle *particle,
                                            float duration) const {
  glm::vec3 elastic_vector = particle->position - attached_particle->position;
  float elasticity_maginitude = elastic_vector.length();

  float elastict_distance = elasticity_maginitude - rest_length;
  if (elastict_distance <= 0) return;

  glm::vec3 elasticity_direction = glm::normalize(elastic_vector);

  glm::vec3 force_applied =
      -spring_constant * elastict_distance * elasticity_direction;
}

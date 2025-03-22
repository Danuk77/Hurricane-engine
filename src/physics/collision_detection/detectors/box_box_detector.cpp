#include "physics/collision_detection/detectors/box_box_detector.hpp"
#include "glm/ext/vector_float2.hpp"

bool collision_detection::is_colliding(const BoxCollider *collider_one,
                                       const BoxCollider *collider_two) {
  return true;
}

glm::vec2 collision_detection::calculate_collision_depth(
    const BoxCollider *collider_one, const BoxCollider *collider_two) {
  return glm::vec2(0.0f);
}

glm::vec2 collision_detection::calculate_collision_normal(
    const BoxCollider *collider_one, const BoxCollider *collider_two) {
  return glm::vec2(0.0f);
}

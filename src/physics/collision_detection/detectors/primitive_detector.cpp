#include <iostream>
#include <optional>

#include "physics/collision_detection/detectors/box_box_detector.hpp"
#include "physics/collision_detection/detectors/primitive_detector.hpp"

std::optional<Collision>
PrimitiveDetector::detect(const BoxCollider &collider_one,
                          const BoxCollider &collider_two) const {
  // TODO: Move this into the box_box_detector module
  BoxColliderEdgeCoordinates collider_one_coordinates =
      generate_box_collider_coordinates(&collider_one);
  BoxColliderEdgeCoordinates collider_two_coordinates =
      generate_box_collider_coordinates(&collider_two);

  if (!is_colliding(&collider_one_coordinates, &collider_two_coordinates)) {
    return std::nullopt;
  }

  glm::vec2 collision_normal =
      calculate_collision_normal(&collider_one, &collider_two);
  float collision_depth = calculate_collision_depth(
      &collider_two_coordinates, &collider_two_coordinates, collision_normal);
  return Collision(collision_depth, collision_normal);
}

std::optional<Collision>
PrimitiveDetector::detect(const CircleCollider &collider_one,
                          const CircleCollider &collider_two) const {
  return std::nullopt;
}
std::optional<Collision>
PrimitiveDetector::detect(const BoxCollider &collider_one,
                          const CircleCollider &collider_two) const {
  return std::nullopt;
}

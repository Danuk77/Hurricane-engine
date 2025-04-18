#include <iostream>
#include <optional>

#include "physics/colliders/circle_collider.hpp"
#include "physics/collision_detection/detectors/box_box_detector.hpp"
#include "physics/collision_detection/detectors/box_circle_detector.hpp"
#include "physics/collision_detection/detectors/circle_circle_detector.hpp"
#include "physics/collision_detection/detectors/primitive_detector.hpp"

std::optional<Collision>
PrimitiveDetector::detect(const BoxCollider &collider_one,
                          const BoxCollider &collider_two) const {
  return evaluate_collision(&collider_one, &collider_two);
}

std::optional<Collision>
PrimitiveDetector::detect(const CircleCollider &collider_one,
                          const CircleCollider &collider_two) const {
  return evaluate_collision(&collider_one, &collider_two);
}
std::optional<Collision>
PrimitiveDetector::detect(const BoxCollider &collider_one,
                          const CircleCollider &collider_two) const {
  return evaluate_collision(&collider_one, &collider_two);
}

std::optional<Collision>
PrimitiveDetector::detect(const CircleCollider &collider_one,
                          const BoxCollider &collider_two) const {
  std::optional<Collision> collision =
      evaluate_collision(&collider_two, &collider_one);

  // Reverse the collision normal as we always calculate the normal in the
  // direction of the box collider
  if (collision) {
    collision->collision_normal = -collision->collision_normal;
  }

  return collision;
}

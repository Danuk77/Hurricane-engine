#include <optional>

#include "physics/collision_detection/detectors/primitive_detector.hpp"

std::optional<Collision>
PrimitiveDetector::detect(const BoxCollider &collider_one,
                          const BoxCollider &collider_two) const {
  return std::nullopt;
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

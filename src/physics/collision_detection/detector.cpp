#include <optional>

#include "physics/collision.hpp"
#include "physics/collision_detection/detector.hpp"
#include "physics/collision_detection/detectors/box_box_detector.hpp"

namespace collision_detection {
std::optional<Collision>
evaluate_possible_collision(const BoxCollider &collider_one,
                            const BoxCollider &collider_two) {
  if (!is_colliding(&collider_one, &collider_two)) {
    return std::nullopt;
  }
  glm::vec2 collision_normal =
      calculate_collision_normal(&collider_one, &collider_two);
  float collision_depth =
      calculate_collision_depth(&collider_one, &collider_two, collision_normal);
  return Collision(collision_depth, collision_normal);
}
} // namespace collision_detection

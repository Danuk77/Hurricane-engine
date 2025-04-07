#include <optional>

#include "physics/collision.hpp"
#include "physics/collision_detection/detector.hpp"
#include "physics/collision_detection/detectors/box_box_detector.hpp"

// std::optional<Collision>
// evaluate_possible_collision(const BoxCollider &collider_one,
//                             const BoxCollider &collider_two) {
//   BoxColliderEdgeCoordinates collider_one_coordinates =
//       generate_box_collider_coordinates(&collider_one);
//   BoxColliderEdgeCoordinates collider_two_coordinates =
//       generate_box_collider_coordinates(&collider_two);
//
//   if (!is_colliding(&collider_one_coordinates, &collider_two_coordinates)) {
//     return std::nullopt;
//   }
//   glm::vec2 collision_normal =
//       calculate_collision_normal(&collider_one, &collider_two);
//   float collision_depth = calculate_collision_depth(
//       &collider_two_coordinates, &collider_two_coordinates,
//       collision_normal);
//   return Collision(collision_depth, collision_normal);
// }

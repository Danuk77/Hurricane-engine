#include <iostream>

#include "glm/ext/quaternion_geometric.hpp"
#include "glm/ext/vector_float2.hpp"
#include "physics/collision_detection/detectors/box_box_detector.hpp"

bool collision_detection::is_colliding(const BoxCollider *collider_one,
                                       const BoxCollider *collider_two) {
  float collider_one_right_edge_x =
      collider_one->transform->position.x + collider_one->half_width;
  float collider_one_left_edge_x =
      collider_one->transform->position.x - collider_one->half_width;
  float collider_one_upper_edge_y =
      collider_one->transform->position.y + collider_one->half_height;
  float collider_one_lower_edge_y =
      collider_one->transform->position.y - collider_one->half_height;

  float collider_two_right_edge_x =
      collider_two->transform->position.x + collider_two->half_width;
  float collider_two_left_edge_x =
      collider_two->transform->position.x - collider_two->half_width;
  float collider_two_upper_edge_y =
      collider_two->transform->position.y + collider_two->half_height;
  float collider_two_lower_edge_y =
      collider_two->transform->position.y - collider_two->half_height;

  bool is_colliding_horizontally =
      collider_one_right_edge_x >= collider_two_left_edge_x &&
      collider_two_right_edge_x >= collider_one_left_edge_x;
  bool is_colliding_vertically =
      collider_one_upper_edge_y >= collider_two_lower_edge_y &&
      collider_two_upper_edge_y >= collider_one_lower_edge_y;

  return is_colliding_vertically && is_colliding_horizontally;
}

glm::vec2 collision_detection::calculate_collision_normal(
    const BoxCollider *collider_one, const BoxCollider *collider_two) {
  return glm::normalize(collider_two->transform->position -
                        collider_one->transform->position);
}

glm::vec2 collision_detection::calculate_collision_depth(
    const BoxCollider *collider_one, const BoxCollider *collider_two) {
  return glm::vec2(0);
}

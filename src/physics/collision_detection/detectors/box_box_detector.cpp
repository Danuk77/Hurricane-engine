#include <algorithm>
#include <iostream>

#include "glm/common.hpp"
#include "glm/ext/vector_float2.hpp"
#include "physics/collision_detection/detectors/box_box_detector.hpp"

std::optional<Collision> evaluate_collision(const BoxCollider *collider_one,
                                            const BoxCollider *collider_two) {
  BoxColliderEdgeCoordinates collider_one_coordinates =
      generate_box_collider_coordinates(collider_one);
  BoxColliderEdgeCoordinates collider_two_coordinates =
      generate_box_collider_coordinates(collider_two);

  if (!is_colliding(&collider_one_coordinates, &collider_two_coordinates)) {
    return std::nullopt;
  }

  glm::vec2 collision_normal =
      calculate_collision_normal(collider_one, collider_two);
  float collision_depth = calculate_collision_depth(
      &collider_two_coordinates, &collider_two_coordinates, collision_normal);
  return Collision(collision_depth, collision_normal);
}

BoxColliderEdgeCoordinates
generate_box_collider_coordinates(const BoxCollider *collider) {
  BoxColliderEdgeCoordinates coordinates;
  coordinates.right_edge_x =
      collider->transform->position.x + collider->half_width;
  coordinates.left_edge_x =
      collider->transform->position.x - collider->half_width;
  coordinates.upper_edge_y =
      collider->transform->position.y + collider->half_height;
  coordinates.lower_edge_y =
      collider->transform->position.y - collider->half_height;

  return coordinates;
}

bool is_colliding(const BoxColliderEdgeCoordinates *collider_one_coordinates,
                  const BoxColliderEdgeCoordinates *collider_two_coordinates) {
  bool is_colliding_horizontally = collider_one_coordinates->right_edge_x >=
                                       collider_two_coordinates->left_edge_x &&
                                   collider_two_coordinates->right_edge_x >=
                                       collider_one_coordinates->left_edge_x;
  bool is_colliding_vertically = collider_one_coordinates->upper_edge_y >=
                                     collider_two_coordinates->lower_edge_y &&
                                 collider_two_coordinates->upper_edge_y >=
                                     collider_one_coordinates->lower_edge_y;

  return is_colliding_vertically && is_colliding_horizontally;
}

glm::vec2 calculate_collision_normal(const BoxCollider *collider_one,
                                     const BoxCollider *collider_two) {
  return glm::normalize(collider_two->transform->position -
                        collider_one->transform->position);
}

float calculate_collision_depth(
    const BoxColliderEdgeCoordinates *collider_one_coordinates,
    const BoxColliderEdgeCoordinates *collider_two_coordinates,
    const glm::vec2 collision_normal) {
  float horizontal_overlap =
      glm::min(glm::abs(collider_one_coordinates->right_edge_x -
                        collider_two_coordinates->left_edge_x),
               glm::abs(collider_one_coordinates->left_edge_x -
                        collider_two_coordinates->right_edge_x));
  float vertical_overlap =
      glm::min(glm::abs(collider_one_coordinates->upper_edge_y -
                        collider_two_coordinates->lower_edge_y),
               glm::abs(collider_one_coordinates->lower_edge_y -
                        collider_two_coordinates->upper_edge_y));

  float collision_depth_in_normal_direction = glm::dot(
      glm::vec2(horizontal_overlap, vertical_overlap), collision_normal);

  return collision_depth_in_normal_direction;
}

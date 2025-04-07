#pragma once
#include "../../colliders/box_collider.hpp"

struct BoxColliderEdgeCoordinates {
  float right_edge_x;
  float left_edge_x;
  float upper_edge_y;
  float lower_edge_y;
};

BoxColliderEdgeCoordinates
generate_box_collider_coordinates(const BoxCollider *collider);
bool is_colliding(const BoxColliderEdgeCoordinates *collider_one_coordinates,
                  const BoxColliderEdgeCoordinates *collider_two_coordinates);
glm::vec2 calculate_collision_normal(const BoxCollider *collider_one,
                                     const BoxCollider *collider_two);
float calculate_collision_depth(
    const BoxColliderEdgeCoordinates *collider_one_coordinates,
    const BoxColliderEdgeCoordinates *collider_two_coordinates,
    const glm::vec2 collision_normal);

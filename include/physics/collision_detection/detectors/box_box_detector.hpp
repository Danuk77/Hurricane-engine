#pragma once
#include <optional>
#include <tuple>

#include "../../colliders/box_collider.hpp"
#include "physics/collision.hpp"

struct BoxColliderEdgeCoordinates {
  float right_edge_x;
  float left_edge_x;
  float upper_edge_y;
  float lower_edge_y;
};

std::optional<Collision> evaluate_collision(const BoxCollider *collider_one,
                                            const BoxCollider *collider_two);
BoxColliderEdgeCoordinates
generate_box_collider_coordinates(const BoxCollider *collider);
bool is_colliding(const BoxColliderEdgeCoordinates *collider_one_coordinates,
                  const BoxColliderEdgeCoordinates *collider_two_coordinates);
Collision
generate_collision(BoxColliderEdgeCoordinates *collider_one_coordinates,
                   BoxColliderEdgeCoordinates *collider_two_coordinates);
std::tuple<int, float> arg_min(float array[], int array_size);
glm::vec2 get_collision_normal(int index);

#pragma once
#include <optional>

#include "../../colliders/circle_collider.hpp"
#include "physics/collision.hpp"
#include "physics/collision_detection/detectors/box_box_detector.hpp"

struct CircleCollisionPreprocessInformation {
  float distance_between_centers;
  float sum_of_radii;
};

std::optional<Collision> evaluate_collision(const CircleCollider &collider_one,
                                            const CircleCollider &collider_two);
CircleCollisionPreprocessInformation
pre_process_circle_collision(const CircleCollider *collider_one,
                             const CircleCollider *collider_two);
bool is_colliding(
    const CircleCollisionPreprocessInformation &collision_information);
glm::vec2 calculate_collision_normal(const CircleCollider *collider_one,
                                     const CircleCollider *collider_two);
float calculate_collision_depth(
    const CircleCollisionPreprocessInformation &collision_information);

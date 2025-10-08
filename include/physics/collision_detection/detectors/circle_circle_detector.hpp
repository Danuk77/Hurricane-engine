#pragma once
#include <optional>

#include "../../colliders/circle_collider.hpp"
#include "physics/contact.hpp"

struct CircleContactPreprocessInformation {
  float distance_between_centers;
  float sum_of_radii;
};

std::optional<Contact> evaluate_collision(const CircleCollider *collider_one,
                                            const CircleCollider *collider_two);
CircleContactPreprocessInformation
pre_process_circle_collision(const CircleCollider *collider_one,
                             const CircleCollider *collider_two);
bool is_colliding(
    const CircleContactPreprocessInformation &collision_information);
glm::vec2 calculate_collision_normal(const CircleCollider *collider_one,
                                     const CircleCollider *collider_two);
float calculate_collision_depth(
    const CircleContactPreprocessInformation &collision_information);

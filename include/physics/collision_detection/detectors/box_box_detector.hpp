#pragma once
#include "../../../glm/vec2.hpp"
#include "../../colliders/box_collider.hpp"

namespace collision_detection {
bool is_colliding(const BoxCollider *collider_one,
                  const BoxCollider *collider_two);
glm::vec2 calculate_collision_depth(const BoxCollider *collider_one,
                                    const BoxCollider *collider_two);
glm::vec2 calculate_collision_normal(const BoxCollider *collider_one,
                                     const BoxCollider *collider_two);
} // namespace collision_detection

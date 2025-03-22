#pragma once
#include <optional>

#include "../collision.hpp"
#include "detectors/box_box_detector.hpp"
#include "physics/colliders/box_collider.hpp"

namespace collision_detection {
std::optional<Collision>
evaluate_possible_collision(const BoxCollider &collider_one,
                            const BoxCollider &collider_two);
}

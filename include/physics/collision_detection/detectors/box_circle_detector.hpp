#pragma once
#include <optional>

#include "../../colliders/box_collider.hpp"
#include "../../colliders/circle_collider.hpp"
#include "physics/contact.hpp"

std::optional<Contact>
evaluate_collision(const BoxCollider *box_collider,
                   const CircleCollider *circle_collider);
glm::vec2 calculate_closest_position_to_circle_on_box(
    const BoxCollider *box_collider, const CircleCollider *circle_collider);

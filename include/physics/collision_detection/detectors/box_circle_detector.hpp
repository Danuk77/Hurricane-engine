#pragma once
#include <optional>

#include "../../colliders/box_collider.hpp"
#include "../../colliders/circle_collider.hpp"
#include "physics/contact.hpp"

std::optional<std::unique_ptr<Contact>>
evaluate_collision(const BoxCollider *box_collider,
                   const CircleCollider *circle_collider);

#pragma once
#include "physics/colliders/circle_collider.hpp"
#include <memory>

std::unique_ptr<CircleCollider>
create_circle_collider(float radius, std::shared_ptr<Transform> transform,
                       std::shared_ptr<Particle> particle);

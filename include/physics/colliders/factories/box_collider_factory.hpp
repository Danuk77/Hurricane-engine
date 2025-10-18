#pragma once
#include "physics/colliders/box_collider.hpp"
#include <memory>

std::unique_ptr<BoxCollider>
create_box_collider(float width, float height,
                    std::shared_ptr<Transform> box_transform,
                    std::shared_ptr<Particle> particle);

#pragma once

#include <vector>

#include "physics/collision.hpp"
#include "physics/collision_detection/detector.hpp"
#include "rendering/scene.hpp"

void run_physics_loop(Scene *scene);
std::vector<Collision> generate_contacts(const CollisionDetector &detector,
                                         Scene *scene);
void apply_forces(Scene *scene);

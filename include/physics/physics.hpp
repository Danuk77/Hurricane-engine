#pragma once

#include "physics/collision_detection/detector.hpp"
#include "rendering/scene.hpp"

void run_physics_loop(const Scene *scene);
void generate_contacts(const CollisionDetector &detector, const Scene *scene);

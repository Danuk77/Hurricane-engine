#pragma once

#include "physics/collision_detection/detector.hpp"
#include "rendering/scene.hpp"

void run_physics_loop(Scene *scene);
void generate_contacts(const CollisionDetector &detector, Scene *scene);
void apply_forces(Scene *scene);

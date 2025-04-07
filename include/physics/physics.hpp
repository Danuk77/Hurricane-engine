#pragma once

#include "physics/collision_detection/detectors/primitive_detector.hpp"
#include "rendering/scene.hpp"

void run_physics_loop(const Scene *scene);
void generate_contacts(const PrimitiveDetector &detector, const Scene *scene);

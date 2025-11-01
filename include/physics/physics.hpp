#pragma once

#include <vector>

#include "physics/contact.hpp"
#include "physics/collision_detection/detector.hpp"
#include "rendering/scene.hpp"

void run_physics_loop(Scene *scene);
std::vector<std::unique_ptr<Contact>> generate_contacts(const ContactDetector &detector,
                                         Scene *scene);
void integrate_step(Scene *scene);
void apply_force_generators();

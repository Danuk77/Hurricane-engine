#include <iostream>
#include <optional>
#include <string>

#include "physics/collision.hpp"
#include "physics/collision_detection/detector.hpp"
#include "physics/physics.hpp"

void run_physics_loop(const Scene *scene) {
  // TODO: (Danuk) Run the coarse collision detector
  // TODO: (Danuk) Extend for arbitrary number of colliders

  std::optional<Collision> collision =
      collision_detection::evaluate_possible_collision(
          scene->game_objects.at(0)->get_collider(),
          scene->game_objects.at(1)->get_collider());
}

#include <iostream>
#include <optional>
#include <string>

#include "physics/collision.hpp"
#include "physics/collision_detection/detector.hpp"
#include "physics/physics.hpp"

void run_physics_loop(const Scene *scene) {
  // TODO: Run the coarse collision detector
  // TODO: Extend for arbitrary number of colliders
  if (scene->game_objects.size() <= 0)
    return;

  return;

  // std::optional<Collision> collision =
  //     collision_detection::evaluate_possible_collision(
  //         scene->game_objects.at(0)->get_collider(),
  //         scene->game_objects.at(1)->get_collider());

  //// TODO: Get rid of
  //// Change the color of the objects when there is a collision
  // if (collision) {
  //   scene->game_objects.at(0)->sprite_color = glm::vec3(1, 0, 0);
  //   scene->game_objects.at(1)->sprite_color = glm::vec3(1, 0, 0);
  // } else {
  //   scene->game_objects.at(0)->sprite_color = glm::vec3(0, 1, 0);
  //   scene->game_objects.at(1)->sprite_color = glm::vec3(0, 1, 0);
  // }
}

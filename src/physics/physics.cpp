#include <iostream>
#include <optional>
#include <string>

#include "physics/collision.hpp"
#include "physics/collision_detection/detector.hpp"
#include "physics/collision_detection/detectors/primitive_detector.hpp"
#include "physics/physics.hpp"

void run_physics_loop(const Scene *scene) {
  PrimitiveDetector detector;

  // TODO: This needs to be replaced by a coarce collision detector which tells
  // us which exact objects need to be checked for collisions
  for (unsigned int i = 0; i < scene->game_objects.size(); i++) {
    for (unsigned int j = i + 1; j < scene->game_objects.size(); j++) {
      Collider &collider_one = scene->game_objects.at(i)->get_collider();
      Collider &collider_two = scene->game_objects.at(i)->get_collider();

      std::optional<Collision> collision =
          collider_one.accept_detector(detector, collider_two);

      // NOTE: Get rid of (Used only for testing)
      // if (collision) {
      //  scene->game_objects.at(0)->sprite_color = glm::vec3(1, 0, 0);
      //  scene->game_objects.at(1)->sprite_color = glm::vec3(1, 0, 0);
      //} else {
      //  scene->game_objects.at(0)->sprite_color = glm::vec3(0, 1, 0);
      //  scene->game_objects.at(1)->sprite_color = glm::vec3(0, 1, 0);
      //}
    }
  }
}

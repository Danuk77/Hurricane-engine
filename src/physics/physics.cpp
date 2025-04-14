#include <iostream>
#include <optional>
#include <vector>

#include "game_objects/gameobject.hpp"
#include "physics/collision.hpp"
#include "physics/collision_detection/detector.hpp"
#include "physics/collision_detection/detectors/primitive_detector.hpp"
#include "physics/physics.hpp"
#include "rendering/scene.hpp"

PrimitiveDetector detector;

// TODO: Add coarce collision detection
// NOTE: We may want to have the physics cycles run at a constant rate (Have it
// run after every x milliseconds)
void run_physics_loop(Scene *scene) {
  apply_forces(scene);
  generate_contacts(detector, scene);
}

void apply_forces(Scene *scene) {
  std::vector<std::unique_ptr<GameObject>>::iterator game_object_iterator;

  for (game_object_iterator = scene->game_objects.begin();
       game_object_iterator != scene->game_objects.end();
       game_object_iterator++) {
    (*game_object_iterator)->apply_forces();
  }
}

// TODO: Return a list of contacts
// TODO: Cleanup
void generate_contacts(const CollisionDetector &detector, Scene *scene) {
  for (unsigned int i = 0; i < scene->game_objects.size(); i++) {
    for (unsigned int j = i + 1; j < scene->game_objects.size(); j++) {
      Collider &collider_one = scene->game_objects.at(i)->get_collider();
      Collider &collider_two = scene->game_objects.at(j)->get_collider();

      std::optional<Collision> collision =
          collider_one.accept_detector(detector, collider_two);

      // NOTE: Get rid of (Used only for testing)
      if (collision) {
        scene->game_objects.at(0)->sprite_color = glm::vec3(1, 0, 0);
        scene->game_objects.at(1)->sprite_color = glm::vec3(1, 0, 0);
      } else {
        scene->game_objects.at(0)->sprite_color = glm::vec3(0, 1, 0);
        scene->game_objects.at(1)->sprite_color = glm::vec3(0, 1, 0);
      }
    }
  }
}

#include <iostream>
#include <optional>
#include <vector>

#include "game_objects/gameobject.hpp"
#include "physics/contact.hpp"
#include "physics/collision_detection/detector.hpp"
#include "physics/collision_detection/detectors/primitive_detector.hpp"
#include "physics/physics.hpp"
#include "rendering/scene.hpp"
#include "data_structures/priority_queue.hpp"

PrimitiveDetector detector;

// TODO: Add coarce collision detection
// NOTE: We may want to have the physics cycles run at a constant rate (Have it
// run after every x milliseconds)
void run_physics_loop(Scene *scene) {
  apply_forces(scene);
  std::vector<Contact> contacts = generate_contacts(detector, scene);
  // TODO:
  // 1. Order the contacts based on their separating velocity (For velocity resolution)
  // 2. Order the contacts based on their penetration (For interpenetration resolution)
  // 3. Resolve velocity
  // 4. Resolve interpenetration
}

void apply_forces(Scene *scene) {
  std::vector<std::unique_ptr<GameObject>>::iterator game_object_iterator;

  for (game_object_iterator = scene->game_objects.begin();
       game_object_iterator != scene->game_objects.end();
       game_object_iterator++) {
    (*game_object_iterator)->apply_forces();
  }
}

// NOTE: This may be able to be refactored using cpp visitor
std::vector<Contact> generate_contacts(const ContactDetector &detector,
                                         Scene *scene) {
  std::vector<Contact> contacts;
  for (unsigned int i = 0; i < scene->game_objects.size(); i++) {
    for (unsigned int j = i + 1; j < scene->game_objects.size(); j++) {
      Collider &collider_one = scene->game_objects.at(i)->get_collider();
      Collider &collider_two = scene->game_objects.at(j)->get_collider();

      std::optional<Contact> collision =
          collider_one.accept_detector(detector, collider_two);

      if (collision) {
        contacts.push_back(collision.value());
        scene->game_objects.at(0)->sprite_color = glm::vec3(1, 0, 0);
        scene->game_objects.at(1)->sprite_color = glm::vec3(1, 0, 0);
      } else {
        scene->game_objects.at(0)->sprite_color = glm::vec3(0, 1, 0);
        scene->game_objects.at(1)->sprite_color = glm::vec3(0, 1, 0);
      }
    }
  }
  return contacts;
}

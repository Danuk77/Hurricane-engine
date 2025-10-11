#include "physics/physics.hpp"

#include <iostream>
#include <memory>
#include <optional>
#include <vector>

#include "game_objects/gameobject.hpp"
#include "physics/collision_detection/detector.hpp"
#include "physics/collision_detection/detectors/primitive_detector.hpp"
#include "physics/collision_resolution/particle_contact_resolver.hpp"
#include "physics/collision_resolution/resolver.hpp"
#include "physics/contact.hpp"
#include "rendering/scene.hpp"

PrimitiveDetector detector;
ParticleContactResolver contact_resolver;

void
run_physics_loop(Scene* scene)
{
  apply_forces(scene);
  std::vector<std::unique_ptr<Contact>> contacts =
    generate_contacts(detector, scene);
  //contact_resolver.resolve_contacts(contacts, 1);
}

void
apply_forces(Scene* scene)
{
  std::vector<std::unique_ptr<GameObject>>::iterator game_object_iterator;

  for (game_object_iterator = scene->game_objects.begin();
       game_object_iterator != scene->game_objects.end();
       game_object_iterator++) {
    (*game_object_iterator)->apply_forces();
  }
}

// NOTE: This may be able to be refactored using cpp visitor
std::vector<std::unique_ptr<Contact>>
generate_contacts(const ContactDetector& detector, Scene* scene)
{
  std::vector<std::unique_ptr<Contact>> contacts;
  for (unsigned int i = 0; i < scene->game_objects.size(); i++) {
    for (unsigned int j = i + 1; j < scene->game_objects.size(); j++) {
      Collider& collider_one = scene->game_objects.at(i)->get_collider();
      Collider& collider_two = scene->game_objects.at(j)->get_collider();

      std::optional<std::unique_ptr<Contact>> contact =
        collider_one.accept_detector(detector, collider_two);

      if (contact) {
        contacts.push_back(std::move(contact.value()));
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

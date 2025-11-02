#include "physics/physics.hpp"

#include <memory>
#include <optional>
#include <vector>

#include "game_objects/gameobject.hpp"
#include "physics/collision_detection/detector.hpp"
#include "physics/collision_detection/detectors/primitive_detector.hpp"
#include "physics/collision_resolution/particle_contact_resolver.hpp"
#include "physics/contact.hpp"
#include "physics/force_generators/gravity.hpp"
#include "rendering/scene.hpp"

PrimitiveDetector detector;
ParticleContactResolver contact_resolver;

void
run_physics_loop(Scene* scene)
{
  apply_force_generators();
  integrate_step(scene);
  std::vector<std::unique_ptr<Contact>> contacts =
    generate_contacts(detector, scene);
  contact_resolver.resolve_contacts(contacts, 1);
}

void
apply_force_generators()
{
  GravityForceGenerator::apply_forces();
};

void
integrate_step(Scene* scene)
{
  for (auto& game_object : scene->game_objects) {
    game_object->integrate_step();
  }
}

// NOTE: This may be able to be refactored using cpp visitor
std::vector<std::unique_ptr<Contact>>
generate_contacts(const ContactDetector& detector, Scene* scene)
{
  std::vector<std::unique_ptr<Contact>> contacts;
  const auto& objects = scene->game_objects;
  
  for (size_t i = 0; i < objects.size(); i++) {
    for (size_t j = i + 1; j < objects.size(); j++) {
      auto& collider_one = objects[i]->get_collider();
      auto& collider_two = objects[j]->get_collider();
      
      if (auto contact = collider_one.accept_detector(detector, collider_two)) {
        contacts.push_back(std::move(*contact));
      }
    }
  }
  return contacts;
}

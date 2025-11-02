#include "game_objects/gameobject.hpp"

GameObject::GameObject(std::string object_name,
                       std::shared_ptr<Transform> transform,
                       std::unique_ptr<Collider> collider,
                       std::shared_ptr<Particle> particle)
  : object_name(std::move(object_name))
  , transform(std::move(transform))
  , collider(std::move(collider))
  , particle(std::move(particle))
{
}

void
GameObject::execute_components()
{
  for (auto& component : components) {
    component->execute_component();
  }
}

void
GameObject::add_component(std::unique_ptr<Component> component)
{
  components.push_back(std::move(component));
}

Particle*
GameObject::get_particle()
{
  return particle.get();
}

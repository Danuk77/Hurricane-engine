#include <algorithm>
#include <memory>
#include <string>
#include <utility>

#include "./transform.hpp"
#include "game_objects/box.hpp"
#include "game_objects/factories/box_factory.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/fwd.hpp"
#include "physics/colliders/box_collider.hpp"
#include "physics/colliders/factories/box_collider_factory.hpp"

std::unique_ptr<Box> create_box(std::string name, float x_position,
                                float y_position, float width, float height,
                                float mass) {
  std::shared_ptr<Transform> box_transform = std::make_shared<Transform>(
      glm::vec2(x_position, y_position), glm::vec2(width, height));
  std::unique_ptr<Particle> particle =
      std::make_unique<Particle>(box_transform, 1 / mass);
  std::unique_ptr<BoxCollider> collider =
      create_box_collider(width, height, box_transform);
  std::unique_ptr<Box> box = std::make_unique<Box>(
      name, box_transform, std::move(collider), std::move(particle));

  return box;
}

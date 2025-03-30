#include <algorithm>
#include <memory>
#include <string>
#include <utility>

#include "./transform.hpp"
#include "game_objects/circle.hpp"
#include "game_objects/factories/circle_factory.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/fwd.hpp"
#include "physics/colliders/factories/circle_collider_factory.hpp"

std::unique_ptr<Circle> create_circle(std::string name, float x_position,
                                      float y_position, float radius) {
  std::shared_ptr<Transform> transform = std::make_shared<Transform>(
      glm::vec2(x_position, y_position), glm::vec2(2 * radius, 2 * radius));
  std::unique_ptr<CircleCollider> collider =
      create_circle_collider(radius, transform);
  std::unique_ptr<Circle> box =
      std::make_unique<Circle>(name, transform, std::move(collider), radius);

  return box;
}

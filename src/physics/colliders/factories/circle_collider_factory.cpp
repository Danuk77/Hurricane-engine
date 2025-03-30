#include <memory>

#include "physics/colliders/circle_collider.hpp"
#include "physics/colliders/factories/circle_collider_factory.hpp"

std::unique_ptr<CircleCollider>
create_circle_collider(float radius, std::shared_ptr<Transform> transform) {
  std::unique_ptr<CircleCollider> collider =
      std::make_unique<CircleCollider>(radius, transform);

  return collider;
}

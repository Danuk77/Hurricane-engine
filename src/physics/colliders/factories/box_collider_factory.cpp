#include <memory>

#include "physics/colliders/factories/box_collider_factory.hpp"

std::unique_ptr<BoxCollider>
create_box_collider(float width, float height,
                    std::shared_ptr<Transform> box_transform) {
  std::unique_ptr<BoxCollider> collider =
      std::make_unique<BoxCollider>(width / 2, height / 2, box_transform);

  return collider;
}

#include <memory>
#include <string>
#include <utility>

#include "./transform.hpp"
#include "game_objects/box.hpp"
#include "game_objects/factories/box_factory.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/fwd.hpp"
#include "physics/colliders/box_collider.hpp"

std::unique_ptr<Box> create_box(std::string name, float x_position,
                                float y_position, float width, float height) {
  Transform box_transform =
      Transform(glm::vec2(x_position, y_position), glm::vec2(width, height));
  std::unique_ptr<BoxCollider> collider =
      std::make_unique<BoxCollider>(BoxCollider(width / 2, height / 2));
  std::unique_ptr<Box> box =
      std::make_unique<Box>(name, box_transform, std::move(collider));
  return box;
}

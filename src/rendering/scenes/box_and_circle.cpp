#include <memory>
#include <utility>

#include "game_objects/box.hpp"
#include "game_objects/circle.hpp"
#include "game_objects/factories/box_factory.hpp"
#include "game_objects/factories/circle_factory.hpp"
#include "rendering/scenes/box_and_circle.hpp"

BoxAndCircle::BoxAndCircle() {
  std::unique_ptr<Box> box = create_box("box_one", 5, 5, 100, 100, 2);
  std::unique_ptr<Circle> circle = create_circle("circle_two", 200, 200, 50, 1);

  add_gameobject(std::move(circle));
  add_gameobject(std::move(box));
}

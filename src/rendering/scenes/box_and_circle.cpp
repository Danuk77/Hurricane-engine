#include <memory>
#include <utility>

#include "game_objects/box.hpp"
#include "game_objects/circle.hpp"
#include "game_objects/factories/box_factory.hpp"
#include "game_objects/factories/circle_factory.hpp"
#include "rendering/scenes/box_and_circle.hpp"

BoxAndCircle::BoxAndCircle() {
  std::unique_ptr<Circle> circle = create_circle("circle_two", 300, 300, 50, .5);
  std::unique_ptr<Box> box = create_box("box_one", 200, 200, 100, 100, .5);

  add_gameobject(std::move(circle));
  add_gameobject(std::move(box));
}

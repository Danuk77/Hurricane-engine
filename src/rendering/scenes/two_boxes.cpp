#include <memory>
#include <utility>

#include "game_objects/box.hpp"
#include "game_objects/factories/box_factory.hpp"
#include "rendering/scenes/two_boxes.hpp"

TwoBoxes::TwoBoxes() {
  std::unique_ptr<Box> box_one = create_box("box_one", 5, 5, 100, 100, 0.5);
  std::unique_ptr<Box> box_two = create_box("box_one", 200, 200, 100, 100, 0.5);

  add_gameobject(std::move(box_one));
  add_gameobject(std::move(box_two));
}

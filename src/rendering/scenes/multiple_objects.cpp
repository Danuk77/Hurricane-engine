#include "rendering/scenes/multiple_objects.hpp"
#include "game_objects/box.hpp"
#include "game_objects/circle.hpp"
#include "game_objects/factories/box_factory.hpp"
#include "game_objects/factories/circle_factory.hpp"

MultipleObjects::MultipleObjects()
{
  std::unique_ptr<Circle> circle =
    create_circle("circle", 20, 20, 25, .5);
  std::unique_ptr<Box> box = create_box("box", 80, 80, 50, 50, .5);
  std::unique_ptr<Box> box_1 = create_box("box_one", 140, 140, 50, 50, .5);
  std::unique_ptr<Box> box_2 = create_box("box_two", 200, 200, 50, 50, .5);
  std::unique_ptr<Box> box_3 = create_box("box_three", 150, 200, 50, 50, .5);
  std::unique_ptr<Circle> circle_1 =
    create_circle("circle_one", 300, 300, 25, .5);
  std::unique_ptr<Circle> circle_2 =
    create_circle("circle_two", 300, 400, 25, .5);

  add_gameobject(std::move(circle));
  add_gameobject(std::move(box));
  add_gameobject(std::move(box_1));
  add_gameobject(std::move(box_2));
  add_gameobject(std::move(box_3));
  add_gameobject(std::move(circle_1));
  add_gameobject(std::move(circle_2));
};

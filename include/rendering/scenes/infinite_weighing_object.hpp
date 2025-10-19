#pragma once

#include "game_objects/box.hpp"
#include "game_objects/circle.hpp"
#include "game_objects/factories/box_factory.hpp"
#include "game_objects/factories/circle_factory.hpp"
#include "rendering/scene.hpp"

class InifiniteWeighingObject : public Scene
{
public:
  InifiniteWeighingObject()
  {
    //std::unique_ptr<Circle> circle = create_circle("circle", 400, 100, 50, -1);
    std::unique_ptr<Circle> circle_1 =
      create_circle("circle", 100, 100, 80, -1);

    //add_gameobject(std::move(circle));

    //std::unique_ptr<Box> box_one = create_box("box_one", 5, 5, 100, 100, 0.5);
    std::unique_ptr<Box> box_two =
      create_box("box_one", 200, 200, 100, 100, .5f);

    //add_gameobject(std::move(box_one));
    add_gameobject(std::move(box_two));
    add_gameobject(std::move(circle_1));
  };
};

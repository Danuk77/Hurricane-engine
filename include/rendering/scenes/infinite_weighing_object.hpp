#pragma once

#include "rendering/scene.hpp"
#include "game_objects/box.hpp"
#include "game_objects/circle.hpp"
#include "game_objects/factories/box_factory.hpp"
#include "game_objects/factories/circle_factory.hpp"

class InifiniteWeighingObject : public Scene
{
public:
  InifiniteWeighingObject()
  {
    std::unique_ptr<Circle> circle = create_circle("circle", 400, 100, 50, -1);
    std::unique_ptr<Circle> circle_1 = create_circle("circle", 100, 100, 50, .5);

    add_gameobject(std::move(circle_1));
    add_gameobject(std::move(circle));
  };
};

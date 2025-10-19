#pragma once

#include "rendering/scene.hpp"
#include "game_objects/box.hpp"
#include "game_objects/circle.hpp"
#include "game_objects/factories/box_factory.hpp"
#include "game_objects/factories/circle_factory.hpp"

class DifferentWeighingObjects : public Scene
{
public:
  DifferentWeighingObjects()
  {
    //std::unique_ptr<Circle> circle = create_circle("circle", 20, 20, 30, .5);
    //std::unique_ptr<Circle> circle_1 = create_circle("circle", 80, 80, 50, .5);

    //add_gameobject(std::move(circle));
    //add_gameobject(std::move(circle_1));

    std::unique_ptr<Box> box = create_box("box", 100, 100, 150, 150, .5);
    std::unique_ptr<Box> box_2 = create_box("box", 300, 300, 50, 50, .5);
    add_gameobject(std::move(box_2));
    add_gameobject(std::move(box));
  };
};

#pragma once

#include "components/character_controller/controller.hpp"
#include "game_objects/box.hpp"
#include "game_objects/circle.hpp"
#include "game_objects/factories/box_factory.hpp"
#include "game_objects/factories/circle_factory.hpp"
#include "physics/force_generators/gravity.hpp"
#include "rendering/scene.hpp"
#include <memory>

class GravityTest : public Scene
{
public:
  GravityTest()
  {
    std::unique_ptr<Circle> circle = create_circle("circle", 100, 100, 50, 1);
    std::unique_ptr<Box> ground = create_box("box_one", 0, 500, 800, 100, -1);

    circle->add_component(std::make_unique<CharacterController>(
      get_window(), circle->get_particle()));
    GravityForceGenerator::subscribe(circle->get_particle());
    add_gameobject(std::move(circle));
    add_gameobject(std::move(ground));
  };
};

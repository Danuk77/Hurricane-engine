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
    std::unique_ptr<Box> box = create_box("box_one", 100, 500, 100, 100, 1);
    //std::unique_ptr<Box> box_two = create_box("box_two", 100, 100, 100, 100, 1);
    std::unique_ptr<Box> ground = create_box("ground", 0, 500, 800, 100, -1);

    box->add_component(
      std::make_unique<CharacterController>(get_window(), box->get_particle()));
    GravityForceGenerator::subscribe(box->get_particle());
    //GravityForceGenerator::subscribe(box_two->get_particle());
    add_gameobject(std::move(box));
    //add_gameobject(std::move(box_two));
    add_gameobject(std::move(ground));
  };
};

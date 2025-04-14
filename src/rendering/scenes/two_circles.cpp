#include <memory>
#include <utility>
#include <vector>

#include "game_objects/factories/circle_factory.hpp"
#include "rendering/scenes/two_circles.hpp"

TwoCircles::TwoCircles() {
  std::unique_ptr<Circle> circle_one =
      create_circle("circle_one", 5, 5, 50, 0.5);
  std::unique_ptr<Circle> circle_two =
      create_circle("circle_two", 200, 200, 50, 0.5);

  add_gameobject(std::move(circle_one));
  add_gameobject(std::move(circle_two));
}

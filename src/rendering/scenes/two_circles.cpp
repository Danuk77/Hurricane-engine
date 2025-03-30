#include <memory>
#include <utility>
#include <vector>

#include "game_objects/factories/circle_factory.hpp"
#include "rendering/scenes/two_circles.hpp"

TwoCircles::TwoCircles() {
  std::unique_ptr<Circle> circle_one = create_circle("circle_one", 5, 5, 50);
  std::unique_ptr<Circle> circle_two =
      create_circle("circle_two", 200, 200, 50);

  add_circle(std::move(circle_one));
  add_circle(std::move(circle_two));
}

void TwoCircles::render() {
  typedef std::vector<std::unique_ptr<Circle>>::iterator game_object_iterator;

  if (circles.size() <= 0) {
    return;
  }

  for (game_object_iterator circle = circles.begin(); circle != circles.end();
       circle++) {
    (*circle)->render();
  }
}

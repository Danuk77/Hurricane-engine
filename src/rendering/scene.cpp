#include <utility>
#include <vector>

#include "game_objects/circle.hpp"
#include "rendering/scene.hpp"

void Scene::add_box(std::unique_ptr<Box> box) {
  game_objects.push_back(std::move(box));
}

void Scene::add_circle(std::unique_ptr<Circle> circle) {
  circles.push_back(std::move(circle));
}

void Scene::render() {
  typedef std::vector<std::unique_ptr<Box>>::iterator game_object_iterator;

  if (game_objects.size() <= 0) {
    return;
  }

  for (game_object_iterator game_object = game_objects.begin();
       game_object != game_objects.end(); game_object++) {
    (*game_object)->render();
  }
}

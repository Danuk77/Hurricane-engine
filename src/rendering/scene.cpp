#include "rendering/scene.hpp"
#include <utility>
#include <vector>

void Scene::add_box(std::unique_ptr<Box> box) {
  game_objects.push_back(std::move(box));
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

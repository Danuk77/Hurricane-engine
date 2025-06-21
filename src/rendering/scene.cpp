#include <utility>
#include <vector>

#include "game_objects/circle.hpp"
#include "rendering/scene.hpp"

void Scene::add_gameobject(std::unique_ptr<GameObject> game_object) {
  game_objects.push_back(std::move(game_object));
}

void Scene::render() {
  typedef std::vector<std::unique_ptr<GameObject>>::iterator
      game_object_iterator;

  if (game_objects.size() <= 0) {
    return;
  }

  for (game_object_iterator game_object = game_objects.begin();
       game_object != game_objects.end(); game_object++) {
    (*game_object)->initialise_model_matrix();
    (*game_object)->render();
  }
}

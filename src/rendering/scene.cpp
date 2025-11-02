#include <utility>
#include <vector>

#include "clock.hpp"
#include "physics/physics.hpp"
#include "rendering/scene.hpp"

void
clear_screen();

void
Scene::add_gameobject(std::unique_ptr<GameObject> game_object)
{
  game_objects.push_back(std::move(game_object));
}

void
Scene::render()
{
  while (!glfwWindowShouldClose(window)) {
    draw_scene();
    Clock::update_time();
    run_physics_loop(this);
    glfwSwapBuffers(window);
    clear_screen();
    glfwPollEvents();
  }
}

void
Scene::draw_scene()
{
  for (auto& game_object : game_objects) {
    game_object->initialise_model_matrix();
    game_object->render();
  }
}

void
clear_screen()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

#define GLFW_USE_WIN32

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <memory>
#include <vector>

#include "./clock.hpp"
#include "input/input_reader.hpp"
#include "physics/physics.hpp"
#include "rendering/scene.hpp"
#include "rendering/scenes/two_boxes.hpp"
#include "rendering/scenes/two_circles.hpp"
#include "rendering/screen.hpp"

void game_loop();
void clear_screen();
void handle_user_input(const Scene &scene, GLFWwindow *window,
                       InputReader *reader);

int main() {
  game_loop();
  return 0;
}

void game_loop() {
  GLFWwindow *window = create_window();
  InputReader reader;
  // TwoBoxes scene;
  TwoCircles scene;

  while (!glfwWindowShouldClose(window)) {
    scene.render();
    Clock::update_time();

    // TODO: Implement for circles
    // handle_user_input(scene, window, &reader);
    // run_physics_loop(&scene);

    glfwSwapBuffers(window);
    clear_screen();
    glfwPollEvents();
  }
}

void clear_screen() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void handle_user_input(const Scene &scene, GLFWwindow *window,
                       InputReader *reader) {
  std::vector<Input> current_frame_inputs = reader->read_user_input(window);
std:
  std::unique_ptr<Box> movable_box;
  if (scene.game_objects.size() > 0) {
    (*scene.game_objects.at(0)).handle_user_input(current_frame_inputs);
  }
}

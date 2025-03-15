#include "rendering/scenes/two_boxes.hpp"
#include <glad/glad.h>
#define GLFW_USE_WIN32
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include "rendering/screen.hpp"

void game_loop();
void clear_screen();

int main(){
  game_loop();
  return 0;
}

void game_loop(){
  GLFWwindow *window = create_window();
  TwoBoxes scene;

  while(!glfwWindowShouldClose(window)){
    scene.render();

    glfwSwapBuffers(window);
    clear_screen();
    glfwPollEvents();
  }
}

void clear_screen(){
  glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}


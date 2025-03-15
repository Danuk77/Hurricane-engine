#define GLFW_USE_WIN32
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
  while(!glfwWindowShouldClose(window)){
    glfwSwapBuffers(window);
    clear_screen();
    glfwPollEvents();
  }
}

void clear_screen(){
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}


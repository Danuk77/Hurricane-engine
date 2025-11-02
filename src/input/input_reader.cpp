#include <vector>

#include "GLFW/glfw3.h"
#include "input/input_reader.hpp"

std::vector<Input> InputReader::read_user_input(GLFWwindow *window) {
  std::vector<Input> current_frame_inputs;

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    current_frame_inputs.push_back(LEFT);
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    current_frame_inputs.push_back(RIGHT);
  }

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    current_frame_inputs.push_back(JUMP);
  }

  return current_frame_inputs;
}

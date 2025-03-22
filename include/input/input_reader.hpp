#pragma once
#include <vector>

#include "GLFW/glfw3.h"
#include "input/input.hpp"

class InputReader {
public:
  InputReader() {}
  std::vector<Input> read_user_input(GLFWwindow *window);

private:
};

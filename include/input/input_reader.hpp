#pragma once
#include "input/input.hpp"
#include "GLFW/glfw3.h"
#include <vector>

class InputReader{
public:
  InputReader(){};
  std::vector<Input> read_user_input(GLFWwindow *window);
private:
};

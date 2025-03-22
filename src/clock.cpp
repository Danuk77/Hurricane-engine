#include "./clock.hpp"
#include "GLFW/glfw3.h"

float Clock::last_frame_time = .0f;
float Clock::delta_time = .0f;

void Clock::update_time() {
  float current_time = glfwGetTime();
  Clock::delta_time = current_time - Clock::last_frame_time;
  Clock::last_frame_time = current_time;
}

float Clock::get_time_since_last_frame() { return delta_time; }

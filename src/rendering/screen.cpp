#include "rendering/screen.hpp"
#include <iostream>

void configure_opengl_version() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// Callback function to handle the window resizing.
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

GLFWwindow *create_window() {
  if (!glfwInit()) {
    std::cout << "Failed to initialise GLFW" << std::endl;
    return nullptr;
  }
  configure_opengl_version();
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Platformer", nullptr, nullptr);

  if (window == nullptr) {
    std::cout << "Couldn't create a GLFW window" << std::endl;
    glfwTerminate();
    return nullptr;
  }

  // Make this windows the current context
  glfwMakeContextCurrent(window);

  // Initialise GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return nullptr;
  }

  // Set the viewport of the opengl context (specifies how much of the window we
  // will take)
  glViewport(0, 0, 800, 600);

  // Register the callback function 'freambuffer_size_callback' to handle window
  // resizing
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  return window;
}

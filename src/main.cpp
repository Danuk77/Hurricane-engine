#define GLFW_USE_WIN32
#include "rendering/scenes/gravity_test.hpp"
#include "data_structures/priority_queue.hpp"

int
main()
{
  GravityTest scene;
  scene.render();
  return 0;
}

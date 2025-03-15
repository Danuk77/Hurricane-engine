#pragma once
#include <glm/glm.hpp>

struct Transform {
  glm::vec2 position;
  glm::vec2 size;

  Transform(glm::vec2 position, glm::vec2 size)
      : position(position), size(size) {}
};

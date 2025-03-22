#pragma once
#include "./collider.hpp"

class BoxCollider : public Collider {
public:
  float half_width;
  float half_height;

  BoxCollider(float half_width, float half_height)
      : half_width(half_width), half_height(half_height) {}
};

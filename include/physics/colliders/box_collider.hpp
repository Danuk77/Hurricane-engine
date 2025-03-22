#pragma once
#include <algorithm>
#include <memory>
#include <utility>

#include "./collider.hpp"
#include "./transform.hpp"

class BoxCollider : public Collider {
public:
  float half_width;
  float half_height;
  std::shared_ptr<Transform> transform;

  BoxCollider(float half_width, float half_height,
              std::shared_ptr<Transform> transform)
      : half_width(half_width), half_height(half_height),
        transform(std::move(transform)) {}
};

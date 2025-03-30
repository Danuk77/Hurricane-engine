#pragma once
#include <algorithm>
#include <memory>
#include <utility>

#include "./collider.hpp"
#include "./transform.hpp"

class CircleCollider : public Collider {
public:
  float radius;
  std::shared_ptr<Transform> transform;

  CircleCollider(float radius, std::shared_ptr<Transform> transform)
      : radius(radius), transform(std::move(transform)) {}
};

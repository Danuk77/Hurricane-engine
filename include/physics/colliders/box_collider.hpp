#pragma once
#include <algorithm>
#include <memory>
#include <optional>
#include <utility>

#include "./collider.hpp"
#include "./transform.hpp"
#include "physics/collision.hpp"

class BoxCollider : public Collider {
public:
  float half_width;
  float half_height;
  std::shared_ptr<Transform> transform;

  BoxCollider(float half_width, float half_height,
              std::shared_ptr<Transform> transform)
      : half_width(half_width), half_height(half_height),
        transform(std::move(transform)) {}

  std::optional<Collision>
  accept_detector(const CollisionDetector &detector,
                  const Collider &collider) const override {
    return collider.accept_detector(detector, *this);
  }
  std::optional<Collision>
  accept_detector(const CollisionDetector &detector,
                  const BoxCollider &box_collider) const override {
    return detector.detect(box_collider, *this);
  }
  std::optional<Collision>
  accept_detector(const CollisionDetector &detector,
                  const CircleCollider &circle_collider) const override {
    return detector.detect(circle_collider, *this);
  }
};

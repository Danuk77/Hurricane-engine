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

  virtual std::optional<Collision>
  accept_detector(const CollisionDetector &detector,
                  const Collider &collider) const {
    return collider.accept_detector(detector, *this);
  }
  virtual std::optional<Collision>
  accept_detector(const CollisionDetector &detector,
                  const BoxCollider &box_collider) const {
    return detector.detect(box_collider, *this);
  }
  virtual std::optional<Collision>
  accept_detector(const CollisionDetector &detector,
                  const CircleCollider &circle_collider) const {
    return detector.detect(*this, circle_collider);
  }
};

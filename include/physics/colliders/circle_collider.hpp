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

  virtual std::optional<Collision>
  accept_detector(const CollisionDetector &detector,
                  const Collider &collider) const {
    collider.accept_detector(detector, *this);
    return std::nullopt;
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

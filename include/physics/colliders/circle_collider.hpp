#pragma once
#include <memory>
#include <utility>

#include "./collider.hpp"
#include "./transform.hpp"
#include "physics/particle.hpp"

class CircleCollider : public Collider {
public:
  float radius;
  std::shared_ptr<Transform> transform;

  CircleCollider(float radius, std::shared_ptr<Transform> transform,
                 std::shared_ptr<Particle> particle)
      : radius(radius), transform(std::move(transform)), Collider(particle) {}

  std::optional<std::unique_ptr<Contact>>
  accept_detector(const ContactDetector &detector,
                  const Collider &collider) const override {
    return collider.accept_detector(detector, *this);
  }
  std::optional<std::unique_ptr<Contact>>
  accept_detector(const ContactDetector &detector,
                  const BoxCollider &box_collider) const override {
    return detector.detect(box_collider, *this);
  }
  std::optional<std::unique_ptr<Contact>>
  accept_detector(const ContactDetector &detector,
                  const CircleCollider &circle_collider) const override {
    return detector.detect(circle_collider, *this);
  }
};

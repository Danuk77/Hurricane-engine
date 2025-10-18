#pragma once
#include <memory>
#include <optional>
#include <utility>

#include "./collider.hpp"
#include "./transform.hpp"
#include "physics/contact.hpp"

class BoxCollider : public Collider {
public:
  float half_width;
  float half_height;
  std::shared_ptr<Transform> transform;

  BoxCollider(float half_width, float half_height,
              std::shared_ptr<Transform> transform,
              std::shared_ptr<Particle> particle)
      : half_width(half_width), half_height(half_height),
        transform(std::move(transform)), Collider(particle) {}

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

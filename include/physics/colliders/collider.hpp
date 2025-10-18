#pragma once

#include <array>
#include <memory>

#include "physics/contact.hpp"
#include "physics/collision_detection/detector.hpp"

class Collider {
public:
  std::shared_ptr<Particle> particle;
  explicit Collider(std::shared_ptr<Particle> particle) : particle(particle) {}
  virtual std::optional<std::unique_ptr<Contact>>
  accept_detector(const ContactDetector &detector,
                  const Collider &collider) const = 0;
  virtual std::optional<std::unique_ptr<Contact>>
  accept_detector(const ContactDetector &detector,
                  const BoxCollider &box_collider) const = 0;
  virtual std::optional<std::unique_ptr<Contact>>
  accept_detector(const ContactDetector &detector,
                  const CircleCollider &circle_collider) const = 0;
};

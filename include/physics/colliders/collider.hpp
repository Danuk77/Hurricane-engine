#pragma once

#include <array>
#include <memory>

#include "physics/collision.hpp"
#include "physics/collision_detection/detector.hpp"

class Collider {
public:
  std::shared_ptr<Particle> particle;
  explicit Collider(std::shared_ptr<Particle> particle) : particle(particle) {}
  virtual std::optional<Collision>
  accept_detector(const CollisionDetector &detector,
                  const Collider &collider) const = 0;
  virtual std::optional<Collision>
  accept_detector(const CollisionDetector &detector,
                  const BoxCollider &box_collider) const = 0;
  virtual std::optional<Collision>
  accept_detector(const CollisionDetector &detector,
                  const CircleCollider &circle_collider) const = 0;
};

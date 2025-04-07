#pragma once
#include <optional>

#include "../collision.hpp"

class BoxCollider;
class CircleCollider;

struct CollisionDetector {
public:
  virtual std::optional<Collision>
  detect(const BoxCollider &collider_one,
         const BoxCollider &collider_two) const = 0;
  virtual std::optional<Collision>
  detect(const CircleCollider &collider_one,
         const CircleCollider &collider_two) const = 0;
  virtual std::optional<Collision>
  detect(const BoxCollider &collider_one,
         const CircleCollider &collider_two) const = 0;
};

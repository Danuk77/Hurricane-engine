#pragma once
#include "physics/collision_detection/detector.hpp"

struct PrimitiveDetector : public CollisionDetector {
public:
  std::optional<Collision>
  detect(const BoxCollider &collider_one,
         const BoxCollider &collider_two) const override;
  std::optional<Collision>
  detect(const CircleCollider &collider_one,
         const CircleCollider &collider_two) const override;
  std::optional<Collision>
  detect(const BoxCollider &collider_one,
         const CircleCollider &collider_two) const override;
};

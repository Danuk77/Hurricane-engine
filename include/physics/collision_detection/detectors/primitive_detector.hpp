#pragma once
#include "physics/collision_detection/detector.hpp"

struct PrimitiveDetector : public ContactDetector {
public:
  std::optional<std::unique_ptr<Contact>>
  detect(const BoxCollider &collider_one,
         const BoxCollider &collider_two) const override;
  std::optional<std::unique_ptr<Contact>>
  detect(const CircleCollider &collider_one,
         const CircleCollider &collider_two) const override;
  std::optional<std::unique_ptr<Contact>>
  detect(const BoxCollider &collider_one,
         const CircleCollider &collider_two) const override;
  std::optional<std::unique_ptr<Contact>>
  detect(const CircleCollider &collider_one,
         const BoxCollider &collider_two) const override;
};

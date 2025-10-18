#pragma once
#include <optional>

#include "../contact.hpp"

class BoxCollider;
class CircleCollider;

struct ContactDetector {
public:
  virtual std::optional<std::unique_ptr<Contact>>
  detect(const BoxCollider &collider_one,
         const BoxCollider &collider_two) const = 0;
  virtual std::optional<std::unique_ptr<Contact>>
  detect(const CircleCollider &collider_one,
         const CircleCollider &collider_two) const = 0;
  virtual std::optional<std::unique_ptr<Contact>>
  detect(const BoxCollider &collider_one,
         const CircleCollider &collider_two) const = 0;
  virtual std::optional<std::unique_ptr<Contact>>
  detect(const CircleCollider &collider_one,
         const BoxCollider &collider_two) const = 0;
};

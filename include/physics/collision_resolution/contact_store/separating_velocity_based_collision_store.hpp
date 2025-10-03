#pragma once

#include "physics/collision.hpp"

class SeparatingVelocityBasedCollisionStore {
public:
  virtual void add_contact(Collision *collision) = 0;
  virtual Collision *get_contact_with_lowest_separating_velocity() = 0;
  virtual void is_empty() = 0;
};

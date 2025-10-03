#pragma once

#include "physics/collision.hpp"

class PenetrationBasedCollisionStore {
public:
  virtual void add_contact(Collision *collision) = 0;
  virtual Collision *get_contact_with_highest_penetration() = 0;
  virtual void is_empty() = 0;
};

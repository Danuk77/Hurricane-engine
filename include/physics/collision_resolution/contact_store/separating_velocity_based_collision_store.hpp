#pragma once

#include "physics/contact.hpp"

class SeparatingVelocityBasedContactStore {
public:
  virtual void add_contact(Contact *contacts) = 0;
  virtual Contact *get_contact_with_lowest_separating_velocity() = 0;
  virtual void is_empty() = 0;
};

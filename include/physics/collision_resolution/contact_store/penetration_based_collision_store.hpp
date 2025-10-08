#pragma once

#include "physics/contact.hpp"

class PenetrationBasedContactStore {
public:
  virtual void add_contact(Contact *collision) = 0;
  virtual Contact *get_contact_with_highest_penetration() = 0;
  virtual void is_empty() = 0;
};

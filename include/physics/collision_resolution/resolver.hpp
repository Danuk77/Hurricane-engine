#pragma once

#include <vector>

#include "physics/contact.hpp"

class ContactResolver {
public:
  virtual void resolve_contacts(std::vector<Contact> contacts,
                                  int max_iterations) = 0;

private:
  virtual void resolve_velocity(std::vector<Contact> contacts,
                                int max_iterations) = 0;
  virtual void resolve_interpenetration(std::vector<Contact> contacts,
                                        int max_iterations) = 0;
};

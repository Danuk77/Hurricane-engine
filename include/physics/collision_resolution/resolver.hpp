#pragma once

#include <memory>
#include <vector>

#include "physics/contact.hpp"

class ContactResolver
{
public:
  virtual void resolve_contacts(const std::vector<std::unique_ptr<Contact>> &contacts,
                                int max_iterations) = 0;

private:
  virtual void resolve_velocity(
    const std::vector<std::unique_ptr<Contact>>& contacts,
    int max_iterations) = 0;
  virtual void resolve_interpenetration(
    const std::vector<std::unique_ptr<Contact>>& collisions,
    int max_iterations) = 0;
};

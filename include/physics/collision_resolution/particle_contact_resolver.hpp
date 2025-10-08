#pragma once

#include "physics/collision_resolution/resolver.hpp"

class ParticleContactResolver : public ContactResolver {
public:
  void resolve_contacts(std::vector<Contact> contacts,
                          int max_iterations) override;

private:
  void resolve_velocity(std::vector<Contact> contacts,
                        int max_iterations) override;
  void resolve_interpenetration(std::vector<Contact> contacts,
                                int max_iterations) override;
};

#pragma once

#include "physics/collision_resolution/resolver.hpp"
#include "physics/collision_resolution/contact_variants/separating_velocity_contact.hpp"
#include <memory>

class ParticleContactResolver : public ContactResolver
{
public:
  void resolve_contacts(const std::vector<std::unique_ptr<Contact>>& contacts,
                        int max_iterations) override;

private:
  void resolve_velocity(const std::vector<std::unique_ptr<Contact>>& contacts,
                        int max_iterations) override;

  void resolve(SeparatingVelocityContact contact);

  void resolve_interpenetration(
    const std::vector<std::unique_ptr<Contact>>& contacts,
    int max_iterations) override;
};

#include "physics/contact.hpp"
#include <memory>
struct SeparatingVelocityContact
{
  const std::unique_ptr<Contact>* contact;

  // NOTE:We will resolve higher separating velocity first. Therefore, we will
  // swap the signs
  const bool operator>(const SeparatingVelocityContact& other)
  {
    return (*contact)->separating_velocity <
           (*other.contact)->separating_velocity;
  };

  const bool operator<(const SeparatingVelocityContact& other)
  {
    return (*contact)->separating_velocity >
           (*other.contact)->separating_velocity;
  };
};

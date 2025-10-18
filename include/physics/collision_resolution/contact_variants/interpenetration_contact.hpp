#include "physics/contact.hpp"
#include <memory>
struct InterpenetrationContact
{
  const std::unique_ptr<Contact>* contact;

  // NOTE:We will resolve higher interpenetration first. Therefore, we will
  // swap the signs
  const bool operator>(const InterpenetrationContact& other)
  {
    return (*contact)->contact_depth <
           (*other.contact)->contact_depth;
  };

  const bool operator<(const InterpenetrationContact& other)
  {
    return (*contact)->contact_depth >
           (*other.contact)->contact_depth;
  };
};

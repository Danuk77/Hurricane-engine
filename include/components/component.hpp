/**
* A base class used for deriving any custom behaviour given to a gameobject
* An example may be a player controller
*/
class Component
{
public:
  virtual void execute_component() = 0;
};

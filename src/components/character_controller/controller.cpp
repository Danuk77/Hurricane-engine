#include "components/character_controller/controller.hpp"
#include "input/input_reader.hpp"

InputReader reader;
const int MOVEMENT_FORCE = 100;
const int JUMP_FORCE = 100000;

void
CharacterController::execute_component()
{
  std::vector<Input> current_frame_inputs = reader.read_user_input(window);
  handle_user_input(current_frame_inputs);
};

void
CharacterController::handle_user_input(std::vector<Input> user_input)
{
  for (auto input : user_input) {
    move(input);
  }
}

void
CharacterController::move(Input direction)
{
  float movement_force = 100;
  switch (direction) {
    case LEFT:
      move_left();
      break;
    case RIGHT:
      move_right();
      break;
    case JUMP:
      jump();
      break;
  }
}

void
CharacterController::move_left()
{
  particle->apply_force(glm::vec2(-MOVEMENT_FORCE, 0));
}

void
CharacterController::move_right()
{
  particle->apply_force(glm::vec2(MOVEMENT_FORCE, 0));
}

// TODO: A jump can only be done once on the ground
void
CharacterController::jump()
{
  // TODO: This is not a proper fix. Fix this once a hook is available to know when the object is grounded
  // SHould only allow when the object is grounded
  if(particle->get_velocity().y < 3 && particle->get_velocity().y > -3){
    particle->apply_force(glm::vec2(0, -JUMP_FORCE));
  }
}

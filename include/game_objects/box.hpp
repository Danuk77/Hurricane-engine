#pragma  once
#include <string>
#include "shaders/shader.hpp"
#include "transform.hpp"
#include "input/input.hpp"
#include <vector>

Shader load_shaders();

class Box{
public:
  std::string box_name;
  Box(std::string box_name, Transform Transform);

  void render();
  void handle_user_input(std::vector<Input> user_input);

private:
  // Game object specific fields
  Transform transform;
  Shader shader_program;
  float movement_velocity = 100.0f;

  // Rendering specific fields
  static unsigned int vertex_array_object, vertex_buffer_object;
  static glm::mat4 projection_matrix;
  glm::mat4 model_matrix;

  void load_shaders();
  void set_vertex_data();
  void initialise_model_matrix();

  void move(Input direction);
  void move_left();
  void move_right();
  void move_up();
  void move_down();
};

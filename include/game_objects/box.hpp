#pragma  once
#include <string>
#include "shaders/shader.hpp"
#include "transform.hpp"

Shader load_shaders();

class Box{
public:
  std::string box_name;

  Box(std::string box_name, Transform Transform);
  void render();

private:
  // Game object specific fields
  Transform transform;
  Shader shader_program;

  // Rendering specific fields
  static unsigned int vertex_array_object, vertex_buffer_object;
  static glm::mat4 projection_matrix;
  glm::mat4 model_matrix;

  void load_shaders();
  void set_vertex_data();
  void initialise_model_matrix();
};

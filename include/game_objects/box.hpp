#pragma once
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "./transform.hpp"
#include "input/input.hpp"
#include "physics/colliders/box_collider.hpp"
#include "shaders/shader.hpp"

Shader load_shaders();

class Box {
public:
  std::string box_name;
  Box(std::string box_name, std::shared_ptr<Transform> Transform,
      std::unique_ptr<BoxCollider> collider);

  void render();
  void handle_user_input(std::vector<Input> user_input);

  BoxCollider &get_collider();

private:
  // Game object specific fields
  std::shared_ptr<Transform> transform;
  std::unique_ptr<BoxCollider> collider;
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

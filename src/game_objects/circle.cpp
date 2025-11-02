#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "game_objects/gameobject.hpp"
#include "glad/glad.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "./clock.hpp"
#include "./file_reader.hpp"
#include "game_objects/circle.hpp"
#include "physics/colliders/circle_collider.hpp"
#include "physics/particle.hpp"
#include "shaders/shader.hpp"

unsigned int Circle::vertex_array_object = 0;
unsigned int Circle::vertex_buffer_object = 0;
glm::mat4 Circle::projection_matrix =
  glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

Circle::Circle(std::string name,
               std::shared_ptr<Transform> transform,
               std::unique_ptr<CircleCollider> collider,
               float radius,
               std::shared_ptr<Particle> particle)
  : GameObject(name, transform, std::move(collider), particle)
  , radius(radius)
{
  set_vertex_data();
  initialise_model_matrix();
  load_shaders();
}

void
Circle::set_vertex_data()
{
  // Check if the vertex array object and vertex buffer objects
  // have already been generated. We only need to do this once.
  // This is because all our 2D elements will be using the same
  // vertex_buffer_object and vertex_array_object
  if (Circle::vertex_array_object == 0) {
    float vertices[] = {
      // clang-format off
      // pos      // tex
      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f
      // clang-format on
    };

    glGenVertexArrays(1, &Circle::vertex_array_object);
    glGenBuffers(1, &Circle::vertex_buffer_object);

    glBindBuffer(GL_ARRAY_BUFFER, Circle::vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(Circle::vertex_array_object);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
      0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void*>(0));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
}

void
Circle::initialise_model_matrix()
{
  model_matrix = glm::mat4(1.0f);
  model_matrix =
    glm::translate(model_matrix, glm::vec3(transform->position, 0.0f));

  // Rotations revolve around the (0,0) point of the model (which is the top
  // left) We need to rotate it around the model's center, therefore move it
  // half its size to the left, rotate and move back
  model_matrix = glm::translate(
    model_matrix,
    glm::vec3(0.5f * transform->size.x, 0.5f * transform->size.y, 0.0f));
  model_matrix =
    glm::rotate(model_matrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  model_matrix = glm::translate(
    model_matrix,
    glm::vec3(-0.5f * transform->size.x, -0.5f * transform->size.y, 0.0f));

  model_matrix = glm::scale(model_matrix, glm::vec3(transform->size, 1.0f));
}

void
Circle::load_shaders()
{
  std::string shader_root_path =
    std::string(PROJECT_ROOT) + "/src/shaders/programs/";
  std::string vertex_shader =
    read_shader_file((shader_root_path + "/circle_vertex_shader.glsl").c_str());
  std::string fragment_shader = read_shader_file(
    (shader_root_path + "/circle_fragment_shader.glsl").c_str());
  shader_program = Shader(vertex_shader.c_str(), fragment_shader.c_str());
}

CircleCollider&
Circle::get_collider()
{
  return static_cast<CircleCollider&>(*collider);
}

void
Circle::render()
{
  shader_program.use();
  shader_program.set_matrix_4("model_matrix", model_matrix);
  shader_program.set_vector_3_float("sprite_color", sprite_color);
  shader_program.set_matrix_4("projection_matrix", Circle::projection_matrix);
  shader_program.set_float("radius", this->radius);
  shader_program.set_vec_2_float("circle_position", this->transform->position);

  glBindBuffer(GL_ARRAY_BUFFER, Circle::vertex_buffer_object);
  glBindVertexArray(Circle::vertex_array_object);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void
Circle::handle_user_input(std::vector<Input> user_input)
{
  std::vector<Input>::iterator user_input_iterator;

  for (user_input_iterator = user_input.begin();
       user_input_iterator != user_input.end();
       user_input_iterator++) {
    move(*user_input_iterator);
  }
}

void
Circle::move(Input direction)
{
  float movement_force = 100;
  switch (direction) {
    case LEFT:
      move_left(movement_force);
      break;
    case RIGHT:
      move_right(movement_force);
      break;
    case UP:
      move_up(movement_force);
      break;
    case DOWN:
      move_down(movement_force);
      break;
  }

  initialise_model_matrix();
}

void
Circle::move_left(float movement_force)
{
  particle->apply_force(glm::vec2(-movement_force, 0));
}

void
Circle::move_right(float movement_force)
{
  particle->apply_force(glm::vec2(movement_force, 0));
}

void
Circle::move_up(float movement_force)
{
  // Up and down is reversed
  particle->apply_force(glm::vec2(0, -movement_force));
}

void
Circle::move_down(float movement_force)
{
  // Up and down is reversed
  particle->apply_force(glm::vec2(0, movement_force));
}

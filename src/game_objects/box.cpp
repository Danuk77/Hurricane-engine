#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "glad/glad.h"
#include "physics/colliders/box_collider.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "./file_reader.hpp"
#include "game_objects/box.hpp"
#include "physics/particle.hpp"
#include "shaders/shader.hpp"

unsigned int Box::vertex_array_object = 0;
unsigned int Box::vertex_buffer_object = 0;
glm::mat4 Box::projection_matrix =
  glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

Box::Box(std::string name,
         std::shared_ptr<Transform> transform,
         std::unique_ptr<BoxCollider> collider,
         std::shared_ptr<Particle> particle)
  : GameObject(name, transform, std::move(collider), particle)
{
  set_vertex_data();
  initialise_model_matrix();
  load_shaders();
}

void
Box::set_vertex_data()
{
  // Check if the vertex array object and vertex buffer objects
  // have already been generated. We only need to do this once.
  // This is because all our 2D elements will be using the same
  // vertex_buffer_object and vertex_array_object
  if (Box::vertex_array_object == 0) {
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

    glGenVertexArrays(1, &Box::vertex_array_object);
    glGenBuffers(1, &Box::vertex_buffer_object);

    glBindBuffer(GL_ARRAY_BUFFER, Box::vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(Box::vertex_array_object);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
      0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void*>(0));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
}

void
Box::initialise_model_matrix()
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
Box::load_shaders()
{
  std::string shader_root_path =
    std::string(PROJECT_ROOT) + "/src/shaders/programs/";
  std::string vertex_shader =
    read_shader_file((shader_root_path + "/vertex_shader.glsl").c_str());
  std::string fragment_shader =
    read_shader_file((shader_root_path + "/fragment_shader.glsl").c_str());
  shader_program = Shader(vertex_shader.c_str(), fragment_shader.c_str());
}

BoxCollider&
Box::get_collider()
{
  return static_cast<BoxCollider&>(*collider);
}

void
Box::render()
{
  shader_program.use();
  shader_program.set_matrix_4("model_matrix", model_matrix);
  shader_program.set_vector_3_float("sprite_color", sprite_color);
  shader_program.set_matrix_4("projection_matrix", Box::projection_matrix);

  glBindBuffer(GL_ARRAY_BUFFER, Box::vertex_buffer_object);
  glBindVertexArray(Box::vertex_array_object);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

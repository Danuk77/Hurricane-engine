#include "game_objects/box.hpp"
#include "glad/glad.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

unsigned int Box::vertex_array_object = 0;
unsigned int Box::vertex_buffer_object = 0;
glm::mat4 Box::projection_matrix = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

Box::Box(std::string box_name, Transform transform): transform(transform){
  set_vertex_data();
  initialise_model_matrix();
}

void Box::set_vertex_data(){
  // Check if the vertex array object and vertex buffer objects
  // have already been generated. We only need to do this once.
  // This is because all our 2D elements will be using the same 
  // vertex_buffer_object and vertex_array_object
  if(Box::vertex_array_object == 0){
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &Box::vertex_array_object);
    glGenBuffers(1, &Box::vertex_buffer_object);

    glBindBuffer(GL_ARRAY_BUFFER, Box::vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(Box::vertex_array_object);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
}

void Box::initialise_model_matrix(){
  model_matrix = glm::mat4(1.0f);
  model_matrix = glm::translate(model_matrix, glm::vec3(transform.position, 0.0f));

  // Rotations revolve around the (0,0) point of the model (which is the top left)
  // We need to rotate it around the model's center, therefore move it half its size to
  // the left, rotate and move back
  model_matrix = glm::translate(model_matrix, glm::vec3(0.5f * transform.size.x, 0.5f * transform.size.y, 0.0f));
  model_matrix = glm::rotate(model_matrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  model_matrix = glm::translate(model_matrix, glm::vec3(-0.5f * transform.size.x, -0.5f * transform.size.y, 0.0f));

  model_matrix = glm::scale(model_matrix, glm::vec3(transform.size, 1.0f));
}

void Box::render(){
  glm::vec3 sprite_color = glm::vec3(1.0f, 1.0f, 1.0f);

  shader_program.use();
  shader_program.set_matrix_4("model_matrix", model_matrix);
  shader_program.set_vector_3_float("sprite_color", sprite_color);
  shader_program.set_matrix_4("projection_matrix", Box::projection_matrix);

  glBindBuffer(GL_ARRAY_BUFFER, Box::vertex_buffer_object);
  glBindVertexArray(Box::vertex_array_object);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

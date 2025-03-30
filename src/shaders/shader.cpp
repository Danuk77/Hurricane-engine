#include <exception>
#include <stdexcept>
#include <string>

#include "glm/gtc/type_ptr.hpp"
#include "shaders/shader.hpp"
/**
 * Interface for loading an interacting with a loaded shader program
 * @param vertex_shader_path The path to the vertex shader source code
 * @param fragment_shader_path The path to the fragment shader source code
 */
Shader::Shader(const char *vertex_shader_code,
               const char *fragment_shader_code) {
  unsigned int vertex_shader =
      compile_shader(vertex_shader_code, VERTEX_SHADER);
  unsigned int fragment_shader =
      compile_shader(fragment_shader_code, FRAGMENT_SHADER);

  create_program(vertex_shader, fragment_shader);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

unsigned int Shader::compile_shader(const char *shader_code,
                                    const shader_type shader_type) {
  unsigned int shader;

  if (shader_type == VERTEX_SHADER) {
    shader = glCreateShader(GL_VERTEX_SHADER);
  } else if (shader_type == FRAGMENT_SHADER) {
    shader = glCreateShader(GL_FRAGMENT_SHADER);
  } else {
    throw std::runtime_error("ERROR::SHADER::LOADING::UNKNOWN SHADER TYPE");
  }

  glShaderSource(shader, 1, &shader_code, NULL);
  glCompileShader(shader);

  check_shader_compile_errors(shader);

  return shader;
}

void Shader::check_shader_compile_errors(unsigned int shader) {
  int compile_status;
  char compile_logs[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
  if (!compile_status) {
    glGetShaderInfoLog(shader, 512, NULL, compile_logs);
    std::string error_message = "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
    error_message.append(compile_logs);
    throw(std::runtime_error(error_message));
  }
}

void Shader::create_program(unsigned int vertex_shader,
                            unsigned int fragment_shader) {
  shader_program_id = glCreateProgram();

  glAttachShader(shader_program_id, vertex_shader);
  glAttachShader(shader_program_id, fragment_shader);
  glLinkProgram(shader_program_id);

  check_shader_linking_errors();
}

void Shader::check_shader_linking_errors() {
  int shader_linking_status;
  char linking_logs[512];

  glGetProgramiv(shader_program_id, GL_LINK_STATUS, &shader_linking_status);
  if (!shader_linking_status) {
    glGetProgramInfoLog(shader_program_id, 512, NULL, linking_logs);
    std::string error_message = "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
    error_message.append(linking_logs);
    throw std::runtime_error(error_message);
  }
}

void Shader::set_matrix_4(std::string matrix_name, glm::mat4 matrix) const {
  this->use();

  auto uniform_location =
      glGetUniformLocation(shader_program_id, matrix_name.c_str());
  glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::set_vector_3_float(std::string vector_name,
                                glm::vec3 vector) const {
  this->use();

  auto uniform_location =
      glGetUniformLocation(shader_program_id, vector_name.c_str());
  glUniform3f(uniform_location, vector.x, vector.y, vector.z);
}

void Shader::set_vec_2_float(std::string vector_name, glm::vec2 vector) const {
  this->use();

  auto uniform_location =
      glGetUniformLocation(shader_program_id, vector_name.c_str());
  glUniform2f(uniform_location, vector.x, vector.y);
}

void Shader::set_int(std::string integer_name, unsigned int integer) const {
  this->use();

  auto uniform_location =
      glGetUniformLocation(shader_program_id, integer_name.c_str());
  glUniform1i(uniform_location, integer);
}

void Shader::set_float(std::string float_name, float float_value) const {
  this->use();

  auto uniform_location =
      glGetUniformLocation(shader_program_id, float_name.c_str());
  glUniform1f(uniform_location, float_value);
}

void Shader::use() const { glUseProgram(shader_program_id); }

#pragma once
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

enum shader_type { VERTEX_SHADER, FRAGMENT_SHADER };

class Shader {
public:
  Shader() {}
  Shader(const char *vertex_shader_code, const char *fragment_shader_code);

  void set_matrix_4(std::string matrix_name, glm::mat4 matrix) const;
  void set_vector_3_float(std::string vector_name, glm::vec3 vector) const;
  void set_int(std::string integer_name, unsigned int integer) const;

  void use() const;

private:
  unsigned int shader_program_id;
  unsigned int compile_shader(const char *shader_code,
                              const shader_type shader_type);
  void check_shader_compile_errors(unsigned int shader);
  void create_program(unsigned int loaded_vertex_shader,
                      unsigned int loaded_fragment_shader);
  void check_shader_linking_errors();
};

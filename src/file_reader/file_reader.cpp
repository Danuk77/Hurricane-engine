#include <file_reader.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

std::string read_shader_file(const char *shader_path) {
  std::ifstream shader_file_buffer;

  // Ensure ifstream objects can throw exceptions
  shader_file_buffer.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    shader_file_buffer.open(shader_path);
    std::stringstream shader_file_string_stream;

    shader_file_string_stream << shader_file_buffer.rdbuf();
    shader_file_buffer.close();

    return shader_file_string_stream.str();
  } catch (std::ifstream::failure e) {
    throw(std::runtime_error("ERROR::SHADER::COULD NOT READ SHADER FILE"));
  }
}

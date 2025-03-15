#pragma once
#include <glad/glad.h>
#include <iostream>

std::string read_shader_file(const char *shader_path);
GLenum identify_format(unsigned int number_of_channels);

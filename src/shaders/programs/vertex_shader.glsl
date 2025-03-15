#version 330 core
layout (location = 0) in vec4 vertex_data;

uniform mat4 model_matrix;
uniform mat4 projection_matrix;

void main(){
  // Set z coordinates to 0.0 as its 2D
  gl_Position = projection_matrix * model_matrix * vec4(vertex_data.xy, 0.0, 1.0f);
}

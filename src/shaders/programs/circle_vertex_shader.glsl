#version 330 core
layout (location = 0) in vec4 vertex_data;

uniform mat4 model_matrix;
uniform mat4 projection_matrix;

out vec4 world_coordinates;

void main(){
  // Set z coordinates to 0.0 as its 2D
  world_coordinates = model_matrix * vec4(vertex_data.xy, 0.0, 1.0f);
  gl_Position = projection_matrix * world_coordinates;
}

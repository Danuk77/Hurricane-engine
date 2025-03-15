#version 330 core
out vec4 output_color;
uniform vec3 sprite_color;

void main(){
  output_color = vec4(sprite_color, 1.0f);
}

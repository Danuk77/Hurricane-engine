#version 330 core
in vec4 world_coordinates;

out vec4 output_color;

uniform vec3 sprite_color;
uniform vec2 circle_position;
uniform float radius;

void main() {
  vec2 circle_center = vec2(circle_position.x + radius, circle_position.y + radius);
  float distance_from_center = distance(world_coordinates.xy, circle_center);

  if(distance_from_center < radius){
    // Calculate some antialiasing so that edges are not so sharp
    float edge_smoothness = 1.0;
    float alpha = smoothstep(radius, radius - edge_smoothness, distance_from_center);

    output_color = vec4(sprite_color, alpha);
  }else{
    output_color = vec4(0.0, 0, 0, 1.0f);
  }
}

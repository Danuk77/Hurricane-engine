#include <array>
#include <stdexcept>
#include <tuple>

#include "glm/common.hpp"
#include "glm/ext/vector_float2.hpp"
#include "physics/contact.hpp"
#include "physics/collision_detection/detectors/box_box_detector.hpp"

std::optional<Contact> evaluate_collision(const BoxCollider *collider_one,
                                            const BoxCollider *collider_two) {
  BoxColliderEdgeCoordinates collider_one_coordinates =
      generate_box_collider_coordinates(collider_one);
  BoxColliderEdgeCoordinates collider_two_coordinates =
      generate_box_collider_coordinates(collider_two);

  if (!is_colliding(&collider_one_coordinates, &collider_two_coordinates)) {
    return std::nullopt;
  }
  return generate_collision(&collider_one_coordinates,
                            &collider_two_coordinates,
                            {collider_one->particle, collider_two->particle});
}

BoxColliderEdgeCoordinates
generate_box_collider_coordinates(const BoxCollider *collider) {
  BoxColliderEdgeCoordinates coordinates;
  coordinates.right_edge_x =
      collider->transform->position.x + collider->half_width;
  coordinates.left_edge_x =
      collider->transform->position.x - collider->half_width;
  coordinates.upper_edge_y =
      collider->transform->position.y + collider->half_height;
  coordinates.lower_edge_y =
      collider->transform->position.y - collider->half_height;

  return coordinates;
}

bool is_colliding(const BoxColliderEdgeCoordinates *collider_one_coordinates,
                  const BoxColliderEdgeCoordinates *collider_two_coordinates) {
  bool is_colliding_horizontally = collider_one_coordinates->right_edge_x >=
                                       collider_two_coordinates->left_edge_x &&
                                   collider_two_coordinates->right_edge_x >=
                                       collider_one_coordinates->left_edge_x;
  bool is_colliding_vertically = collider_one_coordinates->upper_edge_y >=
                                     collider_two_coordinates->lower_edge_y &&
                                 collider_two_coordinates->upper_edge_y >=
                                     collider_one_coordinates->lower_edge_y;

  return is_colliding_vertically && is_colliding_horizontally;
}

Contact
generate_collision(BoxColliderEdgeCoordinates *collider_one_coordinates,
                   BoxColliderEdgeCoordinates *collider_two_coordinates,
                   std::array<std::shared_ptr<Particle>, 2> particles) {
  float right_overlap = glm::abs(collider_one_coordinates->right_edge_x -
                                 collider_two_coordinates->left_edge_x);
  float left_overlap = glm::abs(collider_one_coordinates->left_edge_x -
                                collider_two_coordinates->right_edge_x);
  float upper_overlap = glm::abs(collider_one_coordinates->upper_edge_y -
                                 collider_two_coordinates->lower_edge_y);
  float lower_overlap = glm::abs(collider_one_coordinates->lower_edge_y -
                                 collider_two_coordinates->upper_edge_y);

  float overlap_array[4] = {right_overlap, left_overlap, upper_overlap,
                            lower_overlap};

  std::tuple<int, float> minimum_overlap_values = arg_min(overlap_array, 4);

  glm::vec2 collision_normal =
      get_collision_normal(std::get<0>(minimum_overlap_values));
  float collision_depth = std::get<1>(minimum_overlap_values);

  glm::vec2 relative_velocity = particles[0]->get_velocity() - particles[1]->get_velocity();
  float separating_velocity = glm::dot(relative_velocity, collision_normal);
  return Contact(collision_depth, collision_normal, particles, separating_velocity);
}

std::tuple<int, float> arg_min(float array[], int array_size) {
  float minimum_value = array[0];
  int minimum_value_index = 0;

  if (array_size <= 0) {
    throw std::runtime_error("Array cannot be empty");
  }

  for (unsigned int i = 0; i < array_size; i++) {
    if (array[i] < minimum_value) {
      minimum_value = array[i];
      minimum_value_index = i;
    }
  }

  return std::make_tuple(minimum_value_index, minimum_value);
}

glm::vec2 get_collision_normal(int index) {
  switch (index) {
  case 0:
    return glm::vec2(1, 0);
  case 1:
    return glm::vec2(-1, 0);
  case 2:
    return glm::vec2(0, -1);
  case 3:
    return glm::vec2(0, 1);
  default:
    throw std::runtime_error("Invalid index for collision normal");
  }
}

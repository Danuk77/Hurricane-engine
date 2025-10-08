#include <optional>

#include "glm/common.hpp"
#include "glm/geometric.hpp"
#include "physics/collision_detection/detectors/box_circle_detector.hpp"

std::optional<Contact>
evaluate_collision(const BoxCollider *box_collider,
                   const CircleCollider *circle_collider) {
  glm::vec2 closest_box_point = calculate_closest_position_to_circle_on_box(
      box_collider, circle_collider);
  float distance_from_circle_center_to_closest_box_point =
      glm::distance(circle_collider->transform->position, closest_box_point);

  float collision_depth = circle_collider->radius -
                          distance_from_circle_center_to_closest_box_point;

  if (collision_depth < 0)
    return std::nullopt;

  glm::vec2 collision_normal =
      circle_collider->transform->position - box_collider->transform->position;

  glm::vec2 relative_velocity = box_collider->particle->get_velocity() -
                                circle_collider->particle->get_velocity();
  float separating_velocity = glm::dot(relative_velocity, collision_normal);
  return Contact{collision_depth, collision_normal,
                 {box_collider->particle, circle_collider->particle},
                 separating_velocity};
}

glm::vec2 calculate_closest_position_to_circle_on_box(
    const BoxCollider *box_collider, const CircleCollider *circle_collider) {
  glm::vec2 box_to_circle_vector =
      circle_collider->transform->position - box_collider->transform->position;
  glm::vec2 clamped_box_to_circle_vector =
      glm::vec2(glm::clamp(box_to_circle_vector.x, -box_collider->half_width,
                           box_collider->half_width),
                glm::clamp(box_to_circle_vector.y, -box_collider->half_height,
                           box_collider->half_height));

  return box_collider->transform->position + clamped_box_to_circle_vector;
}

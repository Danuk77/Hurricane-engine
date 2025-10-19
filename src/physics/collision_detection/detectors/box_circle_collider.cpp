#include <iostream>
#include <memory>
#include <optional>

#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "physics/collision_detection/detectors/box_circle_detector.hpp"

glm::vec2
calculate_closest_position_to_circle_on_box(const glm::vec2 box_center,
                                            const glm::vec2 circle_center,
                                            const float box_half_width,
                                            const float box_half_height);

std::optional<std::unique_ptr<Contact>>
evaluate_collision(const BoxCollider* box_collider,
                   const CircleCollider* circle_collider)
{
  glm::vec2 box_center =
    box_collider->transform->position +
    glm::vec2(box_collider->half_width, box_collider->half_height);
  glm::vec2 circle_center =
    circle_collider->transform->position + circle_collider->radius;

  glm::vec2 closest_box_point =
    calculate_closest_position_to_circle_on_box(box_center,
                                                circle_center,
                                                box_collider->half_width,
                                                box_collider->half_height);

  float distance_from_circle_center_to_closest_box_point =
    glm::distance(circle_center, closest_box_point);

  float collision_depth =
    circle_collider->radius - distance_from_circle_center_to_closest_box_point;

  if (collision_depth < 0)
    return std::nullopt;

  glm::vec2 collision_normal =
    glm::normalize(circle_center - closest_box_point);

  glm::vec2 relative_velocity = circle_collider->particle->get_velocity() -
                                box_collider->particle->get_velocity();
  float separating_velocity = glm::dot(relative_velocity, collision_normal);
  return std::make_unique<Contact>(
    Contact{ collision_depth,
             collision_normal,
             { box_collider->particle, circle_collider->particle },
             separating_velocity });
}

glm::vec2
calculate_closest_position_to_circle_on_box(const glm::vec2 box_center,
                                            const glm::vec2 circle_center,
                                            const float box_half_width,
                                            const float box_half_height)
{
  glm::vec2 box_to_circle_vector = circle_center - box_center;
  glm::vec2 clamped_box_to_circle_vector = glm::vec2(
    glm::clamp(box_to_circle_vector.x, -box_half_width, box_half_width),
    glm::clamp(box_to_circle_vector.y, -box_half_height, box_half_height));

  return box_center + clamped_box_to_circle_vector;
}

#include "physics/collision_detection/detectors/circle_circle_detector.hpp"
#include <iostream>
#include <memory>

std::optional<std::unique_ptr<Contact>>
evaluate_collision(const CircleCollider* collider_one,
                   const CircleCollider* collider_two)
{
  CircleContactPreprocessInformation collision_information =
    pre_process_circle_collision(collider_one, collider_two);
  if (!is_colliding(collision_information)) {
    return std::nullopt;
  }

  glm::vec2 collision_normal =
    calculate_collision_normal(collider_one, collider_two);
  float collision_depth = calculate_collision_depth(collision_information);
  glm::vec2 relative_velocity = collider_two->particle->get_velocity() -
                                collider_one->particle->get_velocity();
  float separating_velocity = glm::dot(relative_velocity, collision_normal);
  return std::make_unique<Contact>(
    Contact{ collision_depth,
             collision_normal,
             { collider_one->particle, collider_two->particle },
             separating_velocity });
}

CircleContactPreprocessInformation
pre_process_circle_collision(const CircleCollider* collider_one,
                             const CircleCollider* collider_two)
{
  return CircleContactPreprocessInformation{
    glm::distance(collider_one->transform->position,
                  collider_two->transform->position),
    collider_one->radius + collider_two->radius
  };
}

bool
is_colliding(const CircleContactPreprocessInformation& collision_information)
{
  return collision_information.distance_between_centers <
         collision_information.sum_of_radii;
}

glm::vec2
calculate_collision_normal(const CircleCollider* collider_one,
                           const CircleCollider* collider_two)
{
  return glm::normalize(collider_two->transform->position -
                        collider_one->transform->position);
}

float
calculate_collision_depth(
  const CircleContactPreprocessInformation& collision_information)
{
  return collision_information.sum_of_radii -
         collision_information.distance_between_centers;
}

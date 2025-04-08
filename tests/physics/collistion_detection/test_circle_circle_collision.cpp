#include <gtest/gtest.h>
// clang-format off
#include <algorithm>
// clang-format on

#include <memory>
#include <tuple>

#include "glm/fwd.hpp"
#include "physics/colliders/circle_collider.hpp"
#include "physics/colliders/factories/circle_collider_factory.hpp"
#include "physics/collision_detection/detectors/circle_circle_detector.hpp"

std::shared_ptr<CircleCollider> make_test_collider(glm::vec2 position,
                                                   float radius) {
  return std::shared_ptr<CircleCollider>(create_circle_collider(
      radius, std::make_shared<Transform>(position,
                                          glm::vec2(2 * radius, 2 * radius))));
}

// ###############################################
// ###############################################
// ########## TESTING COLLISION DETECTION ########
// ###############################################
// ###############################################
class CollisionTestParametrizedFixture
    : public ::testing::TestWithParam<
          std::tuple<std::shared_ptr<CircleCollider>,
                     std::shared_ptr<CircleCollider>, bool>> {
protected:
};

TEST_P(CollisionTestParametrizedFixture, TEST_IF_TWO_CIRCLES_COLLIDE) {
  std::shared_ptr<CircleCollider> collider_one = std::get<0>(GetParam());
  std::shared_ptr<CircleCollider> collider_two = std::get<1>(GetParam());
  bool expected_collision_status = std::get<2>(GetParam());

  CircleCollisionPreprocessInformation collision_information =
      pre_process_circle_collision(collider_one.get(), collider_two.get());

  bool collision_status = is_colliding(collision_information);
  ASSERT_EQ(collision_status, expected_collision_status);
}

INSTANTIATE_TEST_CASE_P(
    CollisionTests, CollisionTestParametrizedFixture,
    ::testing::Values(
        // TEST 1
        std::make_tuple(make_test_collider(glm::vec2(5, 5), 5),
                        make_test_collider(glm::vec2(10, 10), 5), true),
        // TEST 2
        std::make_tuple(make_test_collider(glm::vec2(5, 5), 5),
                        make_test_collider(glm::vec2(20, 20), 5), false)));

// #########################################################
// #########################################################
// ########## TESTING CALCULATING COLLISION NORMAL  ########
// #########################################################
// #########################################################

class CollisionNormalCalculationCircle
    : public ::testing::TestWithParam<
          std::tuple<std::shared_ptr<CircleCollider>,
                     std::shared_ptr<CircleCollider>, glm::vec2>> {};

TEST_P(CollisionNormalCalculationCircle,
       TEST_CALCULATING_COLLISION_NORMAL_FOR_CIRCLES) {
  std::shared_ptr<CircleCollider> collider_one = std::get<0>(GetParam());
  std::shared_ptr<CircleCollider> collider_two = std::get<1>(GetParam());

  glm::vec2 expected_collision_normal = std::get<2>(GetParam());
  glm::vec2 collision_normal =
      calculate_collision_normal(collider_one.get(), collider_two.get());

  ASSERT_FLOAT_EQ(collision_normal.x, expected_collision_normal.x);
  ASSERT_FLOAT_EQ(collision_normal.y, expected_collision_normal.y);
}

INSTANTIATE_TEST_CASE_P(
    CollisionTests, CollisionNormalCalculationCircle,
    ::testing::Values(
        // TEST 1
        std::make_tuple(make_test_collider(glm::vec2(5, 5), 5),
                        make_test_collider(glm::vec2(8, 8), 5),
                        glm::vec2(3, 3))));

// #########################################################
// #########################################################
// ########## TESTING CALCULATING COLLISION DEPTH  #########
// #########################################################
// #########################################################
class CollisionDepthCalculationCircle
    : public ::testing::TestWithParam<
          std::tuple<std::shared_ptr<CircleCollider>,
                     std::shared_ptr<CircleCollider>, float>> {};

TEST_P(CollisionDepthCalculationCircle,
       TEST_CALCULATING_COLLISION_DEPTH_FOR_CIRCLES) {
  std::shared_ptr<CircleCollider> collider_one = std::get<0>(GetParam());
  std::shared_ptr<CircleCollider> collider_two = std::get<1>(GetParam());
  float expected_collision_depth = std::get<2>(GetParam());

  CircleCollisionPreprocessInformation collision_information =
      pre_process_circle_collision(collider_one.get(), collider_two.get());

  float collision_depth = calculate_collision_depth(collision_information);

  ASSERT_FLOAT_EQ(collision_depth, expected_collision_depth);
}

INSTANTIATE_TEST_CASE_P(
    CollisionTests, CollisionDepthCalculationCircle,
    ::testing::Values(
        // TEST 1
        std::make_tuple(make_test_collider(glm::vec2(5, 5), 5),
                        make_test_collider(glm::vec2(10, 10), 5), 5),
        // TEST 2
        std::make_tuple(make_test_collider(glm::vec2(5, 5), 10),
                        make_test_collider(glm::vec2(20, 20), 7), 2)));

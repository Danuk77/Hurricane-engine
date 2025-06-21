#include <gtest/gtest.h>
// clang-format off
#include <algorithm>
// clang-format on

#include <memory>
#include <tuple>

#include "glm/exponential.hpp"
#include "glm/fwd.hpp"
#include "physics/colliders/box_collider.hpp"
#include "physics/colliders/factories/box_collider_factory.hpp"
#include "physics/collision_detection/detectors/box_box_detector.hpp"

std::shared_ptr<BoxCollider> make_test_collider(glm::vec2 position, float width,
                                                float height) {
  return std::shared_ptr<BoxCollider>(create_box_collider(
      width, height,
      std::make_shared<Transform>(position, glm::vec2(width, height))));
}

// ###############################################
// ###############################################
// # TESTING BOX COLLIDER COORDINATES GENERATION #
// ###############################################
// ###############################################

TEST(BoxColliderEdgeCoordinatesGeneration, TEST_GENERATING_COORDINATES) {
  std::shared_ptr<BoxCollider> collider =
      make_test_collider(glm::vec2(10, 10), 10, 10);
  BoxColliderEdgeCoordinates coordinates =
      generate_box_collider_coordinates(collider.get());

  EXPECT_EQ(coordinates.left_edge_x, 5);
  EXPECT_EQ(coordinates.right_edge_x, 15);
  EXPECT_EQ(coordinates.upper_edge_y, 15);
  EXPECT_EQ(coordinates.lower_edge_y, 5);
}

// ###############################################
// ###############################################
// ########## TESTING COLLISION DETECTION ########
// ###############################################
// ###############################################
class CollisionTestParametrizedFixture
    : public ::testing::TestWithParam<std::tuple<
          std::shared_ptr<BoxCollider>, std::shared_ptr<BoxCollider>, bool>> {
protected:
};

TEST_P(CollisionTestParametrizedFixture, TEST_IF_TWO_BOXES_COLLIDE) {
  std::shared_ptr<BoxCollider> collider_one = std::get<0>(GetParam());
  std::shared_ptr<BoxCollider> collider_two = std::get<1>(GetParam());
  bool expected_collision_status = std::get<2>(GetParam());

  BoxColliderEdgeCoordinates coordinates_one =
      generate_box_collider_coordinates(collider_one.get());
  BoxColliderEdgeCoordinates coordinates_two =
      generate_box_collider_coordinates(collider_two.get());
  bool collision_status = is_colliding(&coordinates_one, &coordinates_two);
  ASSERT_EQ(collision_status, expected_collision_status);
}

INSTANTIATE_TEST_CASE_P(
    CollisionTests, CollisionTestParametrizedFixture,
    ::testing::Values(
        // TEST 1
        std::make_tuple(make_test_collider(glm::vec2(10, 10), 100, 100),
                        make_test_collider(glm::vec2(50, 100), 100, 100), true),
        // TEST 2
        std::make_tuple(make_test_collider(glm::vec2(10, 0), 30, 30),
                        make_test_collider(glm::vec2(80, 20), 30, 30), false),
        // TEST 3
        std::make_tuple(make_test_collider(glm::vec2(0, 0), 10, 10),
                        make_test_collider(glm::vec2(-10, -10), 50, 50), true),
        // TEST 4
        std::make_tuple(make_test_collider(glm::vec2(0, 0), 10, 10),
                        make_test_collider(glm::vec2(0, 50), 20, 20), false)));

// #########################################################
// #########################################################
// ########## TESTING CALCULATING COLLISION NORMAL  ########
// #########################################################
// #########################################################

class CollisionNormalCalculation
    : public ::testing::TestWithParam<
          std::tuple<std::shared_ptr<BoxCollider>, std::shared_ptr<BoxCollider>,
                     glm::vec2>> {};

TEST_P(CollisionNormalCalculation,
       TEST_CALCULATING_COLLISION_NORMAL_FOR_BOXES) {
  std::shared_ptr<BoxCollider> collider_one = std::get<0>(GetParam());
  std::shared_ptr<BoxCollider> collider_two = std::get<1>(GetParam());

  glm::vec2 expected_collision_normal = std::get<2>(GetParam());
  glm::vec2 collision_normal =
      calculate_collision_normal(collider_one.get(), collider_two.get());

  ASSERT_FLOAT_EQ(collision_normal.x, expected_collision_normal.x);
  ASSERT_FLOAT_EQ(collision_normal.y, expected_collision_normal.y);
}

INSTANTIATE_TEST_CASE_P(
    CollisionTests, CollisionNormalCalculation,
    ::testing::Values(
        // TEST 1
        std::make_tuple(make_test_collider(glm::vec2(10, 10), 100, 100),
                        make_test_collider(glm::vec2(23, 10), 100, 100),
                        glm::vec2(1, 0)),
        // TEST 2
        std::make_tuple(make_test_collider(glm::vec2(32, 15), 30, 30),
                        make_test_collider(glm::vec2(8, -5), 30, 30),
                        glm::vec2(-24 / glm::sqrt(976), -20 / glm::sqrt(976))),
        // TEST 3
        std::make_tuple(make_test_collider(glm::vec2(5, 5), 5, 5),
                        make_test_collider(glm::vec2(10, 10), 5, 3),
                        glm::vec2(5 / glm::sqrt(2 * glm::pow(5, 2))))));

// #########################################################
// #########################################################
// ########## TESTING CALCULATING COLLISION DEPTH  #########
// #########################################################
// #########################################################
class CollisionDepthCalculation
    : public ::testing::TestWithParam<
          std::tuple<std::shared_ptr<BoxCollider>, std::shared_ptr<BoxCollider>,
                     glm::vec2, float>> {};

TEST_P(CollisionDepthCalculation, TEST_CALCULATING_COLLISION_DEPTH_FOR_BOXES) {
  std::shared_ptr<BoxCollider> collider_one = std::get<0>(GetParam());
  std::shared_ptr<BoxCollider> collider_two = std::get<1>(GetParam());
  glm::vec2 collision_normal = std::get<2>(GetParam());
  float expected_collision_depth = std::get<3>(GetParam());

  BoxColliderEdgeCoordinates coordinates_one =
      generate_box_collider_coordinates(collider_one.get());
  BoxColliderEdgeCoordinates coordinates_two =
      generate_box_collider_coordinates(collider_two.get());

  float collision_depth = calculate_collision_depth(
      &coordinates_one, &coordinates_two, collision_normal);

  ASSERT_FLOAT_EQ(collision_depth, expected_collision_depth);
}

INSTANTIATE_TEST_CASE_P(CollisionTests, CollisionDepthCalculation,
                        ::testing::Values(std::make_tuple(
                            make_test_collider(glm::vec2(5, 5), 10, 10),
                            make_test_collider(glm::vec2(10, 10), 10, 6),
                            glm::vec2(5 / glm::sqrt(2 * glm::pow(5, 2))),
                            40 / glm::sqrt(2 * glm::pow(5, 2)))));

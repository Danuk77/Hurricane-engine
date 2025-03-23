#include <gtest/gtest.h>
// clang-format off
#include <algorithm>
// clang-format on

#include <memory>
#include <tuple>

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

  bool collision_status =
      collision_detection::is_colliding(collider_one.get(), collider_two.get());
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
        std::make_tuple(make_test_collider(glm::vec2(0, 0), 10, 10),
                        make_test_collider(glm::vec2(0, 50), 20, 20), false)));

// #########################################################
// #########################################################
// ########## TESTING CALCULATING COLLISION NORMAL  ########
// #########################################################
// #########################################################

// class CollisionNormalCalculation
//     : public ::testing::TestWithParam<
//           std::tuple<std::shared_ptr<BoxCollider>,
//           std::shared_ptr<BoxCollider>,
//                      glm::vec2>> {};
//
// TEST_P(CollisionNormalCalculation, TEST_CALCULATING_COLLISION_NORMAL) {
//   std::shared_ptr<BoxCollider> collider_one = std::get<0>(GetParam());
//   std::shared_ptr<BoxCollider> collider_two = std::get<1>(GetParam());
//
//   glm::vec2 expected_collision_normal = std::get<2>(GetParam());
//   glm::vec2 collision_normal =
//   collision_detection::calculate_collision_normal(
//       collider_one.get(), collider_two.get());
//
//   ASSERT_EQ(collision_normal, expected_collision_normal);
// }
//
//
// INSTANTIATE_TEST_CASE_P(
//     CollisionTests, CollisionNormalCalculation,
//     ::testing::Values(
//         // TEST 1
//         std::make_tuple(std::shared_ptr<BoxCollider>(make_test_collider(glm::vec2(10,
//         10), 100, 100)),
//                         std::shared_ptr<BoxCollider>(make_test_collider(glm::vec2(50,
//                         100), 100, 100)), true),
//         // TEST 2
//         std::make_tuple(std::shared_ptr<BoxCollider>(create_box_collider(
//                             30, 30,
//                             std::make_shared<Transform>(glm::vec2(10, 0),
//                                                         glm::vec2(30, 30)))),
//                         std::shared_ptr<BoxCollider>(create_box_collider(
//                             30, 30,
//                             std::make_shared<Transform>(glm::vec2(80, 20),
//                                                         glm::vec2(30, 30)))),
//                         false)));

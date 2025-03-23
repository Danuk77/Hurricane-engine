// clang-format off
#include <gtest/gtest.h>
// clang-format on

#include <memory>
#include <tuple>

#include "glm/fwd.hpp"
#include "physics/colliders/box_collider.hpp"
#include "physics/colliders/factories/box_collider_factory.hpp"
#include "physics/collision_detection/detectors/box_box_detector.hpp"

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
        std::make_tuple(std::shared_ptr<BoxCollider>(create_box_collider(
                            100, 100,
                            std::make_shared<Transform>(glm::vec2(10, 10),
                                                        glm::vec2(100, 100)))),
                        std::shared_ptr<BoxCollider>(create_box_collider(
                            100, 100,
                            std::make_shared<Transform>(glm::vec2(50, 100),
                                                        glm::vec2(100, 100)))),
                        true),
        // TEST 2
        std::make_tuple(std::shared_ptr<BoxCollider>(create_box_collider(
                            30, 30,
                            std::make_shared<Transform>(glm::vec2(10, 0),
                                                        glm::vec2(30, 30)))),
                        std::shared_ptr<BoxCollider>(create_box_collider(
                            30, 30,
                            std::make_shared<Transform>(glm::vec2(80, 20),
                                                        glm::vec2(30, 30)))),
                        false),
        // TEST 3
        std::make_tuple(std::shared_ptr<BoxCollider>(create_box_collider(
                            10, 10,
                            std::make_shared<Transform>(glm::vec2(0, 0),
                                                        glm::vec2(10, 10)))),
                        std::shared_ptr<BoxCollider>(create_box_collider(
                            50, 50,
                            std::make_shared<Transform>(glm::vec2(-10, -10),
                                                        glm::vec2(50, 50)))),
                        true),
        // TEST 4
        std::make_tuple(std::shared_ptr<BoxCollider>(create_box_collider(
                            10, 10,
                            std::make_shared<Transform>(glm::vec2(0, 0),
                                                        glm::vec2(10, 10)))),
                        std::shared_ptr<BoxCollider>(create_box_collider(
                            10, 20,
                            std::make_shared<Transform>(glm::vec2(0, 50),
                                                        glm::vec2(0, 20)))),
                        false)));

// #########################################################
// #########################################################
// ########## TESTING CALCULATING COLLISION NORMAL  ########
// #########################################################
// #########################################################

class CollisionNormalCalculation
    : public ::testing::TestWithParam<std::tuple<
          std::shared_ptr<BoxCollider>, std::shared_ptr<BoxCollider>, bool>> {};

#pragma once
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "./clock.hpp"
#include "./transform.hpp"
#include "game_objects/gameobject.hpp"
#include "input/input.hpp"
#include "physics/colliders/circle_collider.hpp"
#include "physics/particle.hpp"
#include "shaders/shader.hpp"

Shader load_shaders();

class Circle : public GameObject {
public:
  std::string box_name;
  float radius;

  Circle(std::string circle_name, std::shared_ptr<Transform> Transform,
         std::unique_ptr<CircleCollider> collider, float radius,
         std::shared_ptr<Particle> particle);

  void render() override;
  void handle_user_input(std::vector<Input> user_input) override;
  void apply_forces() override {
    particle->execute_physics_tick(Clock::get_time_since_last_frame());
  }
  Particle *get_particle() override { return particle.get(); };

  CircleCollider &get_collider() override;

private:
  // Game object specific fields
  std::shared_ptr<Transform> transform;
  std::unique_ptr<CircleCollider> collider;
  std::shared_ptr<Particle> particle;
  Shader shader_program;
  float movement_velocity = 100.0f;

  // Rendering specific fields
  static unsigned int vertex_array_object, vertex_buffer_object;
  static glm::mat4 projection_matrix;
  glm::mat4 model_matrix;

  void load_shaders();
  void set_vertex_data();
  void initialise_model_matrix() override;

  void move(Input direction);
  void move_left(float movement_force);
  void move_right(float movement_force);
  void move_up(float movement_force);
  void move_down(float movement_force);
};

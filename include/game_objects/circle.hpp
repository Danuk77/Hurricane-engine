#pragma once
#include <memory>
#include <string>

#include "./clock.hpp"
#include "./transform.hpp"
#include "game_objects/gameobject.hpp"
#include "physics/colliders/circle_collider.hpp"
#include "physics/particle.hpp"
#include "shaders/shader.hpp"

Shader
load_shaders();

class Circle : public GameObject
{
public:
  Circle(std::string circle_name,
         std::shared_ptr<Transform> Transform,
         std::unique_ptr<CircleCollider> collider,
         float radius,
         std::shared_ptr<Particle> particle);
  float radius;
  void render() override;
  void integrate_step() override
  {
    particle->execute_physics_tick(Clock::get_time_since_last_frame());
  }
  CircleCollider& get_collider() override;

private:
  static unsigned int vertex_array_object, vertex_buffer_object;
  static glm::mat4 projection_matrix;
  glm::mat4 model_matrix;

  void load_shaders();
  void set_vertex_data();
  void initialise_model_matrix() override;
};

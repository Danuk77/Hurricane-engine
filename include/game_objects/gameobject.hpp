#pragma once

#include <vector>

#include "glm/ext/vector_float3.hpp"
#include "input/input.hpp"
#include "physics/colliders/collider.hpp"
#include "physics/particle.hpp"
#include "shaders/shader.hpp"

class GameObject
{
public:
  GameObject(std::string object_name,
             std::shared_ptr<Transform> transform,
             std::unique_ptr<Collider> collider,
             std::shared_ptr<Particle> particle)
    : object_name(std::move(object_name))
    , transform(std::move(transform))
    , collider(std::move(collider))
    , particle(std::move(particle))
  {
  }
  std::string object_name;
  glm::vec3 sprite_color = glm::vec3(0, 1, 0);
  virtual void render() = 0;
  virtual void handle_user_input(std::vector<Input> user_input) = 0;
  virtual Collider& get_collider() = 0;
  virtual void integrate_step() = 0;
  virtual void initialise_model_matrix() = 0;
  Particle* get_particle() { return particle.get(); };

protected:
  Shader shader_program;
  float movement_velocity = 100.0f;
  std::shared_ptr<Transform> transform;
  std::unique_ptr<Collider> collider;
  std::shared_ptr<Particle> particle;
};

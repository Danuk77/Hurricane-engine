#pragma once

#include <vector>

#include "components/component.hpp"
#include "glm/ext/vector_float3.hpp"
#include "physics/colliders/collider.hpp"
#include "physics/particle.hpp"
#include "shaders/shader.hpp"

class GameObject
{
public:
  GameObject(std::string object_name,
             std::shared_ptr<Transform> transform,
             std::unique_ptr<Collider> collider,
             std::shared_ptr<Particle> particle);

  std::string object_name;
  glm::vec3 sprite_color = glm::vec3(0, 1, 0);

  virtual void render() = 0;
  virtual Collider& get_collider() = 0;
  virtual void integrate_step() = 0;
  virtual void initialise_model_matrix() = 0;

  Particle* get_particle();
  void execute_components();
  void add_component(std::unique_ptr<Component> component);

protected:
  Shader shader_program;
  float movement_velocity = 100.0f;
  std::shared_ptr<Transform> transform;
  std::unique_ptr<Collider> collider;
  std::shared_ptr<Particle> particle;
  std::vector<std::unique_ptr<Component>> components;
};

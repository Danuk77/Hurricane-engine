#pragma once
#include "physics/particle.hpp"
#include <iostream>
#include <vector>

// NOTE: This utilises the Curiously Recurring Template Pattern (CRTP)
template<typename T>
class ForceGenerator
{
public:
  static void subscribe(Particle* particle)
  {
    auto particle_iterator = T::subscribed_particles.begin();
    for (; particle_iterator != T::subscribed_particles.end();
         particle_iterator++) {
      if (*particle_iterator == particle) {
        std::cout << "Particle already subscribed for gravity" << std::endl;
        return;
      }
    }

    T::subscribed_particles.push_back(particle);
  };
  static void unsubscribe(Particle* particle)
  {
    auto particle_iterator = T::subscribed_particles.begin();
    for (; particle_iterator != T::subscribed_particles.end();
         particle_iterator++) {
      if (*particle_iterator == particle) {
        T::subscribed_particles.erase(particle_iterator);
        return;
      }
    }

    std::cout << "The specified particle to remove is not subscribed to "
                 "gravity generator"
              << std::endl;
  };

  static void apply_forces() { T::apply_forces(); };
};

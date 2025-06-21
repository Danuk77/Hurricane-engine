#pragma once
#include "game_objects/circle.hpp"
#include <memory>
#include <string>

std::unique_ptr<Circle> create_circle(std::string name, float x_position,
                                      float y_position, float radius,
                                      float mass);

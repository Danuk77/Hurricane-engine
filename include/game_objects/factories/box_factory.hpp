#pragma once
#include "game_objects/box.hpp"
#include <memory>
#include <string>

std::unique_ptr<Box> create_box(std::string name, float x_position,
                                float y_position, float width, float height,
                                float mass);

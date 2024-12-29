cmake_minimum_required(VERSION 3.12)
project(Hurricane)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify the source file locations
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB LIBS ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.a)
set(SOURCES ${SRC})

add_executable(Hurricane ${SOURCES})

find_package(OpenGL REQUIRED)

if(NOT ${OPENGL_FOUND})
  message("Could not find package OpenGL")
elseif(NOT ${ASSIMP_FOUND})
  message("Coult not find package Assimp")
else()
  target_include_directories(Hurricane PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIRS})
  target_link_libraries(Hurricane PRIVATE ${OPENGL_LIBRARIES}) 
endif()

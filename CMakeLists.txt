cmake_minimum_required(VERSION 3.12)
project(Hurricane)

add_compile_definitions(PROJECT_ROOT="${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify the source file locations
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Other dependencies
file(GLOB LIBS ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.a)
file(GLOB DEPENDENCIES ${CMAKE_CURRENT_SOURCE_DIR}/src/dep/*.cpp)

set(SOURCES ${SRC} ${DEPENDENCIES})

add_executable(Hurricane ${SOURCES})

find_package(OpenGL REQUIRED)

if(NOT ${OPENGL_FOUND})
  message("Could not find package OpenGL")
else()
  target_include_directories(Hurricane PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include  ${OPENGL_INCLUDE_DIRS})
  target_link_libraries(Hurricane PRIVATE ${OPENGL_LIBRARIES} ${LIBS}) 
endif()

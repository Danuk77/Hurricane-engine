cmake_minimum_required(VERSION 3.12)
project(Hurricane)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify the source file locations
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Helper rendering code (Will be taken out when making it a library)
file(GLOB RENDER ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/*.cpp)

# Other dependencies
file(GLOB LIBS ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.a)
file(GLOB DEPENDENCIES ${CMAKE_CURRENT_SOURCE_DIR}/src/dep/*.cpp)

set(SOURCES ${SRC} ${RENDER} ${DEPENDENCIES})

add_executable(Hurricane ${SOURCES})

find_package(OpenGL REQUIRED)

if(NOT ${OPENGL_FOUND})
  message("Could not find package OpenGL")
else()
  target_include_directories(Hurricane PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include  ${OPENGL_INCLUDE_DIRS})
  target_link_libraries(Hurricane PRIVATE ${OPENGL_LIBRARIES} ${LIBS}) 
endif()

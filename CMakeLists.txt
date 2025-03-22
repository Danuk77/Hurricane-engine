cmake_minimum_required(VERSION 3.12)
project(Hurricane)

add_compile_definitions(PROJECT_ROOT="${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# Test suite setup (GoogleTest)
include(FetchContent)

# Download Googletest for unit testing
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings 
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
message("dir = ${TEST_FILES}")
add_executable(run_test ${TEST_FILES})
target_link_libraries(run_test GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(run_test)

cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(GTest)

enable_testing()

add_executable(
  ${PROJECT_NAME}
  2d-grid_test.cc
  2d-grid.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE ./)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  GTest::gtest_main
)

gtest_discover_tests(${PROJECT_NAME})
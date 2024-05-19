cmake_minimum_required(VERSION 3.2)
project(modules)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -fmodules-ts)

set(${PROJECT_NAME}_SRCS mymodule1.cpp mymodule2.cpp main.cpp)
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRCS})

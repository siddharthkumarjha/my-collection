cmake_minimum_required(VERSION 3.2)
# project(modules)
project(thread)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra)

# set(${PROJECT_NAME}_SRCS mymodule1.cpp mymodule2.cpp main.cpp)
set(${PROJECT_NAME}_SRCS thread.cpp)
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRCS})

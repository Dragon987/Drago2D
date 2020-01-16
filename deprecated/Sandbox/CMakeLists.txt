cmake_minimum_required(VERSION 3.0)
project(Sandbox)

# add_compile_options("-std=c++17")

find_package(drago2d REQUIRED)

add_executable(sandbox main.cpp)
target_link_libraries(sandbox drago2d)
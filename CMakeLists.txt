cmake_minimum_required(VERSION 3.0)
project(collage_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(collage_cpp main.cpp)
target_include_directories(collage_cpp PUBLIC lib)
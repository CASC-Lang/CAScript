cmake_minimum_required(VERSION 3.10)

project(colored VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(colored src/colored.cpp)
target_include_directories(colored PUBLIC include)
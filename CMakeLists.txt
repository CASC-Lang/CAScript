cmake_minimum_required(VERSION 3.0)
project(collage_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(thirdparty/magic_enum)

add_executable(collage_cpp src/main.cpp src/Lexer.cpp)
target_include_directories(collage_cpp PUBLIC include)
target_link_libraries(collage_cpp magic_enum)
cmake_minimum_required(VERSION 3.0)
project(collage_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(thirdparty/magic_enum)

file(GLOB_RECURSE SOURCE_FILES
        src/*.c
        src/*.cpp
        src/*.cc
        src/*.cxx
        src/*.C)
file(GLOB_RECURSE HEADER_FILES
        include/*.h
        include/*.hpp
        include/*.hxx
        include/*.h)
add_executable(collage_cpp ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(collage_cpp PUBLIC include)
target_link_libraries(collage_cpp magic_enum)
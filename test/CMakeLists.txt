cmake_minimum_required(VERSION 3.14)
project(test)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/0134d73a4902574269ff2e42827f7573d3df08ae.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(../thirdparty/magic_enum)

enable_testing(test)

add_executable(
  eval_test
  eval_test.cpp
)
target_include_directories(eval_test PUBLIC ../include ../src)
target_link_libraries(
  eval_test
  gtest_main magic_enum
)

include(GoogleTest)
gtest_discover_tests(eval_test)
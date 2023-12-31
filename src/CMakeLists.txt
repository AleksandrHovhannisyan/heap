cmake_minimum_required(VERSION 3.27)
project(Heap)
set(CMAKE_CXX_STANDARD 20)
add_executable(main main.cpp heap.h)

# Catch2 unit testing
Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)
add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE Catch2::Catch2)
include(CTest)
include(Catch)
catch_discover_tests(tests)

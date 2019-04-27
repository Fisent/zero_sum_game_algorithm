cmake_minimum_required(VERSION 3.5)
project(ZeroSumGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -O0")
set(CMAKE_BUILD_TYPE Debug)

add_library(game src/main.cpp)


add_executable(ZeroSumGame src/main.cpp)
target_link_libraries(ZeroSumGame game)

#GTest
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUnitTests ut/test.cpp ${})
target_link_libraries(runUnitTests gtest gtest_main game)
add_test(ut runUnitTests)

cmake_minimum_required(VERSION 3.5)
project(ZeroSumGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -O0")
set(CMAKE_BUILD_TYPE Debug)

add_library(game src/main.cpp src/game/Board.cpp src/game/Edge.cpp src/game/XmlRpc.cpp)

find_package(XMLRPC REQUIRED c++)

add_executable(ZeroSumGame src/main.cpp src/game/Board.cpp src/game/Edge.cpp src/game/XmlRpc.cpp)
target_link_libraries(ZeroSumGame game xmlrpc_client++ xmlrpc_client xmlrpc++ xmlrpc_util++ xmlrpc  xmlrpc_xmlparse xmlrpc_xmltok xmlrpc_util pthread curl xmlrpc_packetsocket)

#GTest
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUnitTests ut/test.cpp ${})
target_link_libraries(runUnitTests gtest gtest_main game xmlrpc_client++ xmlrpc_client xmlrpc++ xmlrpc_util++ xmlrpc  xmlrpc_xmlparse xmlrpc_xmltok xmlrpc_util pthread curl xmlrpc_packetsocket)
add_test(ut runUnitTests)

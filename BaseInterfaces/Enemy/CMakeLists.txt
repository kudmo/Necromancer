cmake_minimum_required(VERSION 3.16)

project(lab2)

set(CMAKE_CXX_STANDARD 20)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-unused-parameter -std=c++20 -Wall -Wextra")

add_library(Dungeon STATIC source/Dungeon/Dungeon.cpp)
add_library(Floor STATIC source/Floor/Floor.cpp)
add_library(Field STATIC source/Field/Field.cpp)


target_link_libraries(Floor jsoncpp)
target_link_libraries(Floor Field)
target_link_libraries(Dungeon jsoncpp)
target_link_libraries(Dungeon Floor)

target_include_directories(Dungeon PUBLIC include)

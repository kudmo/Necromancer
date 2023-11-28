cmake_minimum_required(VERSION 3.16)
project(CoverageRealizations)

set(CMAKE_CXX_STANDARD 20)

add_library(Wall STATIC source/Wall/Wall.cpp)
add_library(Door STATIC source/Door/Door.cpp)
add_library(Ladder STATIC source/Ladder/Ladder.cpp)

target_link_libraries(Ladder Dungeon)
target_link_libraries(Ladder Entity)
target_link_libraries(Wall Dungeon)
target_link_libraries(Door Dungeon)

target_include_directories(Wall PUBLIC include)
target_include_directories(Door PUBLIC include)
target_include_directories(Ladder PUBLIC include)


cmake_minimum_required(VERSION 3.16)
project(CoverageRealizations)

set(CMAKE_CXX_STANDARD 20)

add_library(Wall STATIC source/Wall/Wall.cpp)
add_library(WallBuilder STATIC source/Wall/WallBuilder.cpp)
set_property(TARGET Wall PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET WallBuilder PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(Door STATIC source/Door/Door.cpp)
add_library(DoorBuilder STATIC source/Door/DoorBuilder.cpp)
set_property(TARGET Door PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET DoorBuilder PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(Ladder STATIC source/Ladder/Ladder.cpp)
add_library(LadderBuilder STATIC source/Ladder/LadderBuilder.cpp)
set_property(TARGET Ladder PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET LadderBuilder PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Ladder Dungeon)
target_link_libraries(Ladder Entity)
target_link_libraries(Wall Dungeon)
target_link_libraries(Door Dungeon)

target_link_libraries(DoorBuilder Door)
target_link_libraries(LadderBuilder Ladder)
target_link_libraries(WallBuilder Wall)

target_link_libraries(DoorBuilder Dungeon)
target_link_libraries(DoorBuilder Floor)
target_link_libraries(DoorBuilder Field)

target_link_libraries(LadderBuilder Dungeon)
target_link_libraries(LadderBuilder Floor)
target_link_libraries(LadderBuilder Field)

target_link_libraries(WallBuilder Dungeon)
target_link_libraries(WallBuilder Floor)
target_link_libraries(WallBuilder Field)

target_include_directories(Wall PUBLIC include)
target_include_directories(WallBuilder PUBLIC include)

target_include_directories(Door PUBLIC include)
target_include_directories(DoorBuilder PUBLIC include)

target_include_directories(Ladder PUBLIC include)
target_include_directories(LadderBuilder PUBLIC include)
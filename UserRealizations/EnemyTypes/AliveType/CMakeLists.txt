cmake_minimum_required(VERSION 3.16)
project(AliveTypeRealizations)

set(CMAKE_CXX_STANDARD 20)

add_library(Goblin STATIC source/Goblin/Goblin.cpp)
add_library(Alive::Goblin ALIAS Goblin)

add_library(Ogr STATIC source/Ogr/Ogr.cpp)
add_library(Alive::Ogr ALIAS Ogr)

target_link_libraries(Goblin AliveType)
target_link_libraries(Ogr AliveType)

target_include_directories(Goblin PUBLIC include)
target_include_directories(Ogr PUBLIC include)

cmake_minimum_required(VERSION 3.16)
project(CoverageRealizations)

set(CMAKE_CXX_STANDARD 20)

add_library(Magma STATIC source/Magma/Magma.cpp)
add_library(MagmaBuilder STATIC source/Magma/MagmaBuilder.cpp)

target_link_libraries(Magma Interfaces)
target_link_libraries(Magma Entity)

target_link_libraries(MagmaBuilder Magma)

target_link_libraries(MagmaBuilder Dungeon)
target_link_libraries(MagmaBuilder Floor)
target_link_libraries(MagmaBuilder Field)

target_include_directories(Magma PUBLIC include)
target_include_directories(MagmaBuilder PUBLIC include)

cmake_minimum_required(VERSION 3.16)
project(CoverageRealizations)

set(CMAKE_CXX_STANDARD 20)

add_library(Magma STATIC source/Magma/Magma.cpp)

target_link_libraries(Magma Interfaces)
target_link_libraries(Magma Entity)

target_include_directories(Magma PUBLIC include)

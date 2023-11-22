cmake_minimum_required(VERSION 3.16)

project(lab2)

set(CMAKE_CXX_STANDARD 20)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-unused-parameter -std=c++20 -Wall -Wextra")

add_library(Entity STATIC source/Entity.cpp)

target_include_directories(Entity PUBLIC include)

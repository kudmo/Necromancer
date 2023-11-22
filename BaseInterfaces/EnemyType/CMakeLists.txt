cmake_minimum_required(VERSION 3.16)
project(EnemyType)

set(CMAKE_CXX_STANDARD 20)

add_library(EnemyType STATIC source/EnemyType.cpp)

target_include_directories(EnemyType PUBLIC include)

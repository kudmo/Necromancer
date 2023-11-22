cmake_minimum_required(VERSION 3.16)

project(lab3)

set(CMAKE_CXX_STANDARD 20)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-unused-parameter -std=c++20 -Wall -Wextra")

add_subdirectory(BaseInterfaces/Dungeon)
add_subdirectory(BaseInterfaces/Object)
add_subdirectory(BaseInterfaces/Items)
add_subdirectory(BaseInterfaces/Entity)
add_subdirectory(BaseInterfaces/Enemy)
add_subdirectory(BaseInterfaces/EnemyType)

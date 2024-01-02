cmake_minimum_required(VERSION 3.16)
project(Alive)

set(CMAKE_CXX_STANDARD 20)

add_library(Alive STATIC source/Alive/Alive.cpp)
add_library(AliveType STATIC source/AliveType/AliveType.cpp)

set_property(TARGET Alive PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET AliveType PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Alive Enemy)
target_link_libraries(Alive Interfaces)
target_link_libraries(Alive AliveType)
target_link_libraries(Alive DeadBody)
target_link_libraries(Alive Floor)
target_link_libraries(Alive Field)
target_link_libraries(Alive Dungeon)

target_link_libraries(AliveType  EnemyType)

target_include_directories(Alive PUBLIC include)
target_include_directories(AliveType PUBLIC include)

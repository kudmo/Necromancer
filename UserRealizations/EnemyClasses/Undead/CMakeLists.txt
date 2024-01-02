cmake_minimum_required(VERSION 3.16)
project(Undead)

set(CMAKE_CXX_STANDARD 20)

add_library(Undead STATIC source/Undead/Undead.cpp)
add_library(UndeadType STATIC source/UndeadType/UndeadType.cpp)

set_property(TARGET Undead PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET UndeadType PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Undead  Enemy)
target_link_libraries(Undead  Interfaces)
target_link_libraries(Undead  UndeadType)
target_link_libraries(Undead  DeadBody)
target_link_libraries(Undead  Floor)

target_link_libraries(UndeadType  AliveType)
target_link_libraries(UndeadType  EnemyType)

target_include_directories(Undead PUBLIC include)
target_include_directories(UndeadType PUBLIC include)

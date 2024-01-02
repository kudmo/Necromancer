cmake_minimum_required(VERSION 3.16)
project(Enemy)

set(CMAKE_CXX_STANDARD 20)

add_library(Enemy STATIC source/Enemy/Enemy.cpp)
add_library(EnemyType STATIC source/EnemyType/EnemyType.cpp)

set_property(TARGET Enemy PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET EnemyType PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Enemy Entity)
target_link_libraries(Enemy Floor)
target_link_libraries(Enemy Field)
target_link_libraries(Enemy EnemyType)
target_link_libraries(Enemy SubSkill)
target_link_libraries(Enemy Interfaces)

target_include_directories(Enemy PUBLIC include)
target_include_directories(EnemyType PUBLIC include)

cmake_minimum_required(VERSION 3.16)
project(Enemy)

set(CMAKE_CXX_STANDARD 20)

add_library(Enemy STATIC source/Enemy.cpp)

target_link_libraries(Enemy Entity)
target_link_libraries(Enemy Floor)
target_link_libraries(Enemy EnemyType)

target_include_directories(Dungeon PUBLIC include)

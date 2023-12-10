cmake_minimum_required(VERSION 3.16)

project(Game)

set(CMAKE_CXX_STANDARD 20)

add_library(Game source/Game.cpp)

target_link_libraries(Game Dungeon)
target_link_libraries(Game Floor)
target_link_libraries(Game Field)

target_link_libraries(Game Player)
target_link_libraries(Game Entity)
target_link_libraries(Game Enemy)
target_link_libraries(Game GlobalSkillManager)

target_include_directories(Game PUBLIC include)
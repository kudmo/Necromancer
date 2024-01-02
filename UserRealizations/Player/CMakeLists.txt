cmake_minimum_required(VERSION 3.16)
project(Player)

set(CMAKE_CXX_STANDARD 20)

add_library(Player STATIC source/Player/Player.cpp)

set_property(TARGET Player PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Player SkillTable)
target_link_libraries(Player MainSkill)
target_link_libraries(Player Entity)
target_link_libraries(Player Undead)
target_link_libraries(Player GlobalEnemyManager)
target_link_libraries(Player GlobalSkillManager)

target_include_directories(Object PUBLIC include)

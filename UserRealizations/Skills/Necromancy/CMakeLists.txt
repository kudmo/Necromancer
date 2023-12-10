cmake_minimum_required(VERSION 3.16)
project(SkillCurse)

set(CMAKE_CXX_STANDARD 20)

add_library(MainNecromancy STATIC source/Main/Necromancy.cpp)
add_library(VariationNecromancy STATIC source/Variations/NecromancyVariation.cpp)

target_link_libraries(MainNecromancy VariationNecromancy)
target_link_libraries(MainNecromancy MainSkill)
target_link_libraries(MainNecromancy SubSkill)
target_link_libraries(MainNecromancy Object)
target_link_libraries(MainNecromancy Entity)

target_link_libraries(MainNecromancy Player)
target_link_libraries(MainNecromancy DeadBody)
target_link_libraries(MainNecromancy Field)
target_link_libraries(MainNecromancy Floor)

target_link_libraries(VariationNecromancy Entity)
target_link_libraries(VariationNecromancy Object)

target_include_directories(MainNecromancy PUBLIC include)
target_include_directories(VariationNecromancy PUBLIC include)

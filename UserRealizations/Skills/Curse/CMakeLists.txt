cmake_minimum_required(VERSION 3.16)
project(SkillCurse)

set(CMAKE_CXX_STANDARD 20)

add_library(MainCurse STATIC source/Main/Curse.cpp)
add_library(VariationCurse STATIC source/Variations/CurseVariation.cpp)

target_link_libraries(MainCurse VariationCurse)
target_link_libraries(MainCurse Entity)
target_link_libraries(MainCurse Object)
target_link_libraries(MainCurse MainSkill)
target_link_libraries(MainCurse SubSkill)
target_link_libraries(MainCurse Player)

target_link_libraries(VariationCurse Entity)
target_link_libraries(VariationCurse Object)
target_link_libraries(VariationCurse SubSkill)
target_link_libraries(VariationCurse Player)

target_include_directories(MainCurse PUBLIC include)
target_include_directories(VariationCurse PUBLIC include)

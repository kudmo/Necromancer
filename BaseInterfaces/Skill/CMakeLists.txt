cmake_minimum_required(VERSION 3.16)
project(Skill)

set(CMAKE_CXX_STANDARD 20)


add_library(SkillTable STATIC source/SkillTable/SkillTable.cpp)
add_library(MainSkill STATIC source/MainSkill/MainSkill.cpp)
add_library(SubSkill STATIC source/SubSkill/SubSkill.cpp)

target_link_libraries(SkillTable MainSkill)
target_link_libraries(SkillTable Entity)
target_link_libraries(SkillTable Object)

target_link_libraries(MainSkill SubSkill)
target_link_libraries(MainSkill Entity)
target_link_libraries(MainSkill Object)

target_link_libraries(SubSkill Entity)
target_link_libraries(SubSkill Object)

target_include_directories(MainSkill PUBLIC include)
target_include_directories(SubSkill PUBLIC include)
target_include_directories(SkillTable PUBLIC include)

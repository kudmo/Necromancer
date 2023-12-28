cmake_minimum_required(VERSION 3.16)

project(plugins-golem-stone)

set(CMAKE_CXX_STANDARD 20)

add_library(StoneGolem STATIC source/StoneGolem.cpp)
add_library(Golem::StoneGolem ALIAS StoneGolem)
set_property(TARGET StoneGolem PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(StoneGolemType STATIC source/StoneGolemType.cpp)
set_property(TARGET StoneGolemType PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(StoneGolem PRIVATE Golem)
target_link_libraries(StoneGolem PRIVATE StoneGolemType)
target_link_libraries(StoneGolem PRIVATE Dungeon)
target_link_libraries(StoneGolem PRIVATE Floor)
target_link_libraries(StoneGolem PRIVATE Field)
target_link_libraries(StoneGolem PRIVATE Wall)

target_link_libraries(StoneGolemType PRIVATE GolemType)


add_library(StoneGolemBuilder SHARED builder.cpp)
set_property(TARGET StoneGolemBuilder PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(StoneGolemBuilder PRIVATE Golem::StoneGolem)
target_link_libraries(StoneGolemBuilder PRIVATE GolemType)
target_link_libraries(StoneGolemBuilder PRIVATE Golem)

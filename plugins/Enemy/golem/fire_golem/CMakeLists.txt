cmake_minimum_required(VERSION 3.16)

project(plugins-golem-fire)

set(CMAKE_CXX_STANDARD 20)

add_library(FireGolem STATIC source/FireGolem.cpp)
add_library(Golem::FireGolem ALIAS FireGolem)
set_property(TARGET FireGolem PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(FireGolemType STATIC source/FireGolemType.cpp)
set_property(TARGET FireGolemType PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(FireGolem PRIVATE FireGolemType)
target_link_libraries(FireGolem PRIVATE Golem)
target_link_libraries(FireGolem PRIVATE Dungeon)
target_link_libraries(FireGolem PRIVATE Floor)
target_link_libraries(FireGolem PRIVATE Field)
target_link_libraries(FireGolem PRIVATE Magma)

target_link_libraries(FireGolemType PRIVATE GolemType)

add_library(FireGolemBuilder SHARED builder.cpp)
set_property(TARGET FireGolemBuilder PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(FireGolemBuilder PRIVATE Golem::FireGolem)
target_link_libraries(FireGolemBuilder PRIVATE GolemType)
target_link_libraries(FireGolemBuilder PRIVATE Golem)

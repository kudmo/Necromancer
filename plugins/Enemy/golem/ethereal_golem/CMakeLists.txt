cmake_minimum_required(VERSION 3.16)

project(plugins-golem-ethereal)

set(CMAKE_CXX_STANDARD 20)

add_library(EtherealGolem STATIC source/EtherealGolem.cpp)
add_library(Golem::EtherealGolem ALIAS EtherealGolem)
set_property(TARGET EtherealGolem PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(EtherealGolemType STATIC source/EtherealGolemType.cpp)
set_property(TARGET EtherealGolemType PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(EtherealGolem PRIVATE EtherealGolemType)
target_link_libraries(EtherealGolem PRIVATE Golem)
target_link_libraries(EtherealGolem PRIVATE Dungeon)
target_link_libraries(EtherealGolem PRIVATE Floor)
target_link_libraries(EtherealGolem PRIVATE Field)

target_link_libraries(EtherealGolemType PRIVATE GolemType)


add_library(EtherealGolemBuilder SHARED builder.cpp)
set_property(TARGET EtherealGolemBuilder PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(EtherealGolemBuilder PRIVATE Golem::EtherealGolem)
target_link_libraries(EtherealGolemBuilder PRIVATE GolemType)
target_link_libraries(EtherealGolemBuilder PRIVATE Golem)

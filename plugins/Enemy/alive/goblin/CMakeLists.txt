cmake_minimum_required(VERSION 3.16)

project(plugins-alive-goblin)

set(CMAKE_CXX_STANDARD 20)

add_library(Goblin STATIC source/Goblin.cpp)
add_library(Alive::Goblin ALIAS Goblin)
set_property(TARGET Goblin PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Goblin PRIVATE AliveType)


add_library(GoblinBuilder SHARED builder.cpp)
set_property(TARGET GoblinBuilder PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(GoblinBuilder PRIVATE Alive::Goblin)
target_link_libraries(GoblinBuilder PRIVATE AliveType)
target_link_libraries(GoblinBuilder PRIVATE Alive)


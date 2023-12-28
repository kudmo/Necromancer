cmake_minimum_required(VERSION 3.16)

project(plugins-undead-ghoul)

set(CMAKE_CXX_STANDARD 20)

add_library(Ghoul STATIC source/Ghoul.cpp)
add_library(Undead::Ghoul ALIAS Ghoul)
set_property(TARGET Ghoul PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Ghoul PRIVATE UndeadType)
target_link_libraries(Ghoul PRIVATE AliveType)
target_link_libraries(Ghoul PRIVATE MainNecromancy)

add_library(GhoulBuilder SHARED builder.cpp)
set_property(TARGET GhoulBuilder PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(GhoulBuilder PRIVATE Undead::Ghoul)
target_link_libraries(GhoulBuilder PRIVATE UndeadType)
target_link_libraries(GhoulBuilder PRIVATE Undead)

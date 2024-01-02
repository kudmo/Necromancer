cmake_minimum_required(VERSION 3.16)

project(plugins-undead-fantomas)

set(CMAKE_CXX_STANDARD 20)

add_library(Fantomas STATIC source/Fantomas.cpp)
add_library(Undead::Fantomas ALIAS Fantomas)
set_property(TARGET Fantomas PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Fantomas PRIVATE UndeadType)
target_link_libraries(Fantomas PRIVATE AliveType)
target_link_libraries(Fantomas PRIVATE MainNecromancy)
target_link_libraries(Fantomas PRIVATE VariationNecromancy)
target_link_libraries(Fantomas PRIVATE MainMorphism)
target_link_libraries(Fantomas PRIVATE VariationMorphism)

add_library(FantomasBuilder SHARED builder.cpp)
set_property(TARGET FantomasBuilder PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(FantomasBuilder PRIVATE Undead::Fantomas)
target_link_libraries(FantomasBuilder PRIVATE UndeadType)
target_link_libraries(FantomasBuilder PRIVATE Undead)
target_link_libraries(FantomasBuilder PRIVATE MainNecromancy)
target_link_libraries(FantomasBuilder PRIVATE VariationNecromancy)
target_link_libraries(FantomasBuilder PRIVATE MainMorphism)
target_link_libraries(FantomasBuilder PRIVATE VariationMorphism)
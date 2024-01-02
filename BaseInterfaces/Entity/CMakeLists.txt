cmake_minimum_required(VERSION 3.16)
project(Entity)

set(CMAKE_CXX_STANDARD 20)

add_library(Entity STATIC source/Entity.cpp)

set_property(TARGET Entity PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Entity Object)
target_link_libraries(Entity Floor)
target_link_libraries(Entity Field)
target_link_libraries(Entity Interfaces)


target_include_directories(Entity PUBLIC include)

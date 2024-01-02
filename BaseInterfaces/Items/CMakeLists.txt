cmake_minimum_required(VERSION 3.16)
project(Item)

set(CMAKE_CXX_STANDARD 20)

add_library(Item STATIC source/Item.cpp)

set_property(TARGET Item PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Item  Object)
target_link_libraries(Item  Floor)
target_link_libraries(Item  Field)

target_include_directories(Item PUBLIC include)
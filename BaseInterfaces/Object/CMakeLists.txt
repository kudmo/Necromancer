cmake_minimum_required(VERSION 3.16)
project(Object)

set(CMAKE_CXX_STANDARD 20)

add_library(Object STATIC source/Object.cpp)

set_property(TARGET Object PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Object Floor)
target_link_libraries(Object Field)
target_link_libraries(Object Interfaces)

target_include_directories(Object PUBLIC include)

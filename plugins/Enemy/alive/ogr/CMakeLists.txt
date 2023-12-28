cmake_minimum_required(VERSION 3.16)

project(plugins-alive-ogr)

set(CMAKE_CXX_STANDARD 20)

add_library(Ogr STATIC source/Ogr.cpp)
add_library(Alive::Ogr ALIAS Ogr)
set_property(TARGET Ogr PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Ogr PRIVATE AliveType)


add_library(OgrBuilder SHARED builder.cpp)
set_property(TARGET OgrBuilder PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(OgrBuilder PRIVATE Alive::Ogr)
target_link_libraries(OgrBuilder PRIVATE AliveType)
target_link_libraries(OgrBuilder PRIVATE Alive)
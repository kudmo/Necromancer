cmake_minimum_required(VERSION 3.16)
project(GlobalItemManager)

set(CMAKE_CXX_STANDARD 20)

add_library(GlobalItemManager STATIC source/GlobalItemManager.cpp)
set_property(TARGET GlobalItemManager PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(GlobalItemManager Dungeon)

target_include_directories(GlobalItemManager PUBLIC include)
cmake_minimum_required(VERSION 3.16)
project(GlobalItemManager)

set(CMAKE_CXX_STANDARD 20)

add_library(GlobalItemManager STATIC source/GlobalItemManager.cpp)

target_link_libraries(GlobalItemManager Dungeon)

target_include_directories(GlobalItemManager PUBLIC include)
cmake_minimum_required(VERSION 3.16)

project(MenuController)

set(CMAKE_CXX_STANDARD 20)

add_library(MenuController source/MenuController.cpp)

target_link_libraries(MenuController MenuView)

target_include_directories(MenuController PUBLIC include)
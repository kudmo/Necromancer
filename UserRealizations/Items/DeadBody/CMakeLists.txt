cmake_minimum_required(VERSION 3.16)
project(DeadBody)

set(CMAKE_CXX_STANDARD 20)

add_library(DeadBody STATIC source/DeadBody/DeadBody.cpp)

target_link_libraries(DeadBody Item)
target_link_libraries(DeadBody AliveType)

target_include_directories(DeadBody PUBLIC include)

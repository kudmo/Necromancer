cmake_minimum_required(VERSION 3.16)

project(lab3)

set(CMAKE_CXX_STANDARD 20)


find_package(Threads REQUIRED)
link_libraries(Threads::Threads)

add_subdirectory(Game)
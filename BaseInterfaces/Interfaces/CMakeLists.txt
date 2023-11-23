cmake_minimum_required(VERSION 3.16)
project(Interfaces)

set(CMAKE_CXX_STANDARD 20)

add_library(Interfaces INTERFACE)
target_include_directories(Interfaces INTERFACE ./)
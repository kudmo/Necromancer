cmake_minimum_required(VERSION 3.16)
project(UndeadTypeRealizations)

set(CMAKE_CXX_STANDARD 20)

add_library(Skeleton STATIC source/Skeleton/Skeleton.cpp)
add_library(Ghoul STATIC source/Ghoul/Ghoul.cpp)

target_link_libraries(Skeleton UndeadType)
target_link_libraries(Skeleton AliveType)

target_link_libraries(Ghoul UndeadType)
target_link_libraries(Ghoul AliveType)

target_include_directories(Skeleton PUBLIC include)
target_include_directories(Ghoul PUBLIC include)

cmake_minimum_required(VERSION 3.16)
project(Golem)

set(CMAKE_CXX_STANDARD 20)

add_library(Golem STATIC source/Golem/Golem.cpp)
add_library(GolemType STATIC source/GolemType/GolemType.cpp)

target_link_libraries(Golem Enemy)
target_link_libraries(Golem Interfaces)
target_link_libraries(Golem GolemType)
target_link_libraries(Golem DeadBody)

target_link_libraries(GolemType EnemyType)

target_include_directories(Golem PUBLIC include)
target_include_directories(GolemType PUBLIC include)

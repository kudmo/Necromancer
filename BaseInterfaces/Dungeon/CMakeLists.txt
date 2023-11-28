cmake_minimum_required(VERSION 3.16)
project(Dungeon)

set(CMAKE_CXX_STANDARD 20)

add_library(Dungeon STATIC source/Dungeon/Dungeon.cpp)
add_library(Floor STATIC source/Floor/Floor.cpp)
add_library(Field STATIC source/Field/Field.cpp)

target_link_libraries(Field Entity)
target_link_libraries(Field Item)

target_link_libraries(Field Magma)
target_link_libraries(Field Wall)
target_link_libraries(Field Door)
target_link_libraries(Field Ladder)

target_link_libraries(Floor jsoncpp)
target_link_libraries(Floor Dungeon)
target_link_libraries(Floor Field)
target_link_libraries(Floor Entity)
target_link_libraries(Floor Matrix)
target_link_libraries(Floor Item)

target_link_libraries(Floor Magma)
target_link_libraries(Floor Wall)
target_link_libraries(Floor Door)
target_link_libraries(Floor Ladder)


target_link_libraries(Dungeon jsoncpp)
target_link_libraries(Dungeon Floor)
target_link_libraries(Dungeon Entity)

target_include_directories(Dungeon PUBLIC include)
target_include_directories(Floor PUBLIC include)
target_include_directories(Field PUBLIC include)
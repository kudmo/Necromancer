cmake_minimum_required(VERSION 3.16)
project(Dungeon)

set(CMAKE_CXX_STANDARD 20)

add_library(Dungeon STATIC source/Dungeon/Dungeon.cpp)
add_library(Floor STATIC source/Floor/Floor.cpp)
add_library(Field STATIC source/Field/Field.cpp)

target_link_libraries(Field Entity)
target_link_libraries(Field Item)

target_link_libraries(Floor jsoncpp)
target_link_libraries(Floor Dungeon)
target_link_libraries(Floor Field)
target_link_libraries(Floor Entity)
target_link_libraries(Floor Matrix)

target_link_libraries(Dungeon jsoncpp)
target_link_libraries(Dungeon Floor)
target_link_libraries(Dungeon Entity)

target_include_directories(Dungeon PUBLIC include)

cmake_minimum_required(VERSION 3.16)

project(Views)

set(CMAKE_CXX_STANDARD 20)

add_executable(view-test main.cpp)

add_subdirectory(Dungeon)
add_subdirectory(Menu)

target_link_libraries(view-test FloorView)
target_link_libraries(view-test DungeonView)
target_link_libraries(view-test Game)

target_link_libraries(view-test Floor)
target_link_libraries(view-test Player)

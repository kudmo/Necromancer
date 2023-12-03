cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

project(Tests)

find_package(Catch2 2 REQUIRED)

add_executable(tests testing_main.cpp)
target_link_libraries(tests Catch2::Catch2)

target_link_libraries(tests Matrix)

target_link_libraries(tests Dungeon)
target_link_libraries(tests Floor)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Game/input_files/test_dungeon.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/input_files/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Game/input_files/test_floor.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/input_files/)

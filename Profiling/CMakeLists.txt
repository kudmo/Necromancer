cmake_minimum_required(VERSION 3.16)

project(profiling)

set(CMAKE_CXX_STANDARD 20)

add_executable(profiling main.cpp)
target_link_libraries(profiling Game)
target_link_libraries(profiling Dungeon)

add_custom_target(copy_target_stupid_tests ALL
        ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/input_files ${CMAKE_CURRENT_BINARY_DIR}/input_files
        DEPENDS profiling
        COMMENT "Copy needed folder(input_files) to compiling profiling"
)

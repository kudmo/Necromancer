cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

project(Tests)

find_package(Catch2 2 REQUIRED)

add_executable(tests testing_main.cpp)
target_link_libraries(tests Catch2::Catch2)

target_link_libraries(tests Matrix)

target_link_libraries(tests Dungeon)
target_link_libraries(tests Floor)

target_link_libraries(tests Player)
target_link_libraries(tests GlobalSkillManager)
target_link_libraries(tests GlobalEnemyManager)

add_custom_target(copy_target_tests ALL
        ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Game/input_files ${CMAKE_CURRENT_BINARY_DIR}/Game/input_files
        DEPENDS tests
        COMMENT "Copy neded folder(input_files) to compiling tests"
)


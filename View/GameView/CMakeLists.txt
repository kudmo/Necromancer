cmake_minimum_required(VERSION 3.16)

project(GameView)

set(CMAKE_CXX_STANDARD 20)

add_library(GameView GameView.cpp)
add_library(GameViewController GameViewController.cpp)
add_library(AdminElements AdminElements.cpp AdminElements.h)
add_library(PlayerInfoView PlayerInfoView.cpp PlayerInfoView.h)

target_link_libraries(PlayerInfoView sfml-graphics sfml-window sfml-system)
target_link_libraries(PlayerInfoView Player)

target_link_libraries(GameViewController GameView)
target_link_libraries(GameViewController Game)
target_link_libraries(GameViewController MenuController)

target_link_libraries(GameView sfml-graphics sfml-window sfml-system)
target_link_libraries(GameView FloorView)
target_link_libraries(GameView PlayerInfoView)
target_link_libraries(GameView Floor)
target_link_libraries(GameView MenuView)
target_link_libraries(GameView MenuController)

target_link_libraries(GameView AdminElements)

target_link_libraries(AdminElements sfml-graphics sfml-window sfml-system)
target_link_libraries(AdminElements MenuController)

target_include_directories(GameView PUBLIC ./)
target_include_directories(GameViewController PUBLIC ./)

add_custom_target(copy_target_player_info_view_1 ALL
        ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/input_files ${CMAKE_CURRENT_BINARY_DIR}/input_files
        DEPENDS PlayerInfoView
        COMMENT "Copy needed folder(input_files) to compiling PlayerInfoView"
)
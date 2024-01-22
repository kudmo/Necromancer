cmake_minimum_required(VERSION 3.16)

project(DungeonViews)

set(CMAKE_CXX_STANDARD 20)

add_library(FloorView Floor_View.cpp)
add_library(DungeonView Dungeon_View.cpp)
add_library(EntityView Entity_View.cpp)
add_library(ItemView Item_View.cpp)

target_link_libraries(DungeonView Dungeon)
target_link_libraries(DungeonView Floor)
target_link_libraries(DungeonView FloorView)

target_link_libraries(FloorView sfml-graphics sfml-window sfml-system)
target_link_libraries(FloorView jsoncpp)
target_link_libraries(FloorView Field)
target_link_libraries(FloorView Floor)
target_link_libraries(FloorView Entity)
target_link_libraries(FloorView Player)
target_link_libraries(FloorView EntityView)
target_link_libraries(FloorView ItemView)

target_link_libraries(EntityView sfml-graphics sfml-window sfml-system)
target_link_libraries(EntityView Entity)
target_link_libraries(EntityView jsoncpp)


target_link_libraries(ItemView sfml-graphics sfml-window sfml-system)
target_link_libraries(ItemView Item)
target_link_libraries(ItemView jsoncpp)

target_include_directories(FloorView PUBLIC ./)

add_custom_target(copy_target_view_dungeon_1 ALL
        ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/sprites ${CMAKE_CURRENT_BINARY_DIR}/sprites
        DEPENDS EntityView
        COMMENT "Copy needed folder(sprites) to compiling executable 1"
)

add_custom_target(copy_target_view_dungeon_2 ALL
        ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/input_files ${CMAKE_CURRENT_BINARY_DIR}/input_files
        DEPENDS FloorView
        COMMENT "Copy needed folder(input_files) to compiling executable 2"
)
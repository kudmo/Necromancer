cmake_minimum_required(VERSION 3.16)

project(MenuViews)

set(CMAKE_CXX_STANDARD 20)

add_library(MenuView source/MenuView.cpp)
target_link_libraries(MenuView sfml-graphics sfml-window sfml-system)

add_custom_target(copy_target_view_menu_image ALL
        ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/image ${CMAKE_CURRENT_BINARY_DIR}/image
        DEPENDS MenuView
        COMMENT "Copy needed folder(image) to compiling menu"
)

add_custom_target(copy_target_view_menu_font ALL
        ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/font ${CMAKE_CURRENT_BINARY_DIR}/font
        DEPENDS MenuView
        COMMENT "Copy needed folder(font) to compiling menu"
)

target_include_directories(MenuView PUBLIC include)
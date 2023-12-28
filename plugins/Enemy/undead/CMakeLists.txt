cmake_minimum_required(VERSION 3.16)

project(plugins-undead)

set(CMAKE_CXX_STANDARD 20)

FILE(GLOB children ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(dir ${children})
    IF(IS_DIRECTORY ${dir})
        message(STATUS "adding plugin from - ${dir}")
        add_subdirectory(${dir})
    ELSE()
        CONTINUE()
    ENDIF()
endforeach()

message(STATUS "adding manager for it - UndeadManager")

add_library(UndeadManager STATIC UndeadManager.cpp)
target_link_libraries(UndeadManager dl)
target_include_directories(UndeadManager PUBLIC ./)
set_property(TARGET UndeadManager PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(UndeadManager Enemy)
target_link_libraries(UndeadManager Undead)
target_link_libraries(UndeadManager UndeadType)

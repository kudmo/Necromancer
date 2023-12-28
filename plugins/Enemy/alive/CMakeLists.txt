cmake_minimum_required(VERSION 3.16)

project(plugins-alive)

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

message(STATUS "adding manager for it - AliveManager")

add_library(AliveManager STATIC AliveManager.cpp)
target_link_libraries(AliveManager dl)
target_include_directories(AliveManager PUBLIC ./)
set_property(TARGET AliveManager PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(AliveManager Enemy)
target_link_libraries(AliveManager Alive)
target_link_libraries(AliveManager AliveType)

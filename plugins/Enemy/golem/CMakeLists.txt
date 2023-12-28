cmake_minimum_required(VERSION 3.16)

project(plugins-golem)

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

message(STATUS "adding manager for it - GolemManager")

add_library(GolemManager STATIC GolemManager.cpp)
target_link_libraries(GolemManager dl)
target_include_directories(GolemManager PUBLIC ./)
set_property(TARGET GolemManager PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(GolemManager Enemy)
target_link_libraries(GolemManager Golem)
target_link_libraries(GolemManager GolemType)

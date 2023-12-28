cmake_minimum_required(VERSION 3.16)

project(plugins-undead-ghoul)

set(CMAKE_CXX_STANDARD 20)

add_library(Skeleton STATIC source/Skeleton.cpp)
add_library(Undead::Skeleton ALIAS Skeleton)
set_property(TARGET Skeleton PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Skeleton PRIVATE UndeadType)
target_link_libraries(Skeleton PRIVATE AliveType)
target_link_libraries(Skeleton PRIVATE MainNecromancy)


target_include_directories(Skeleton PUBLIC include)

add_library(SkeletonBuilder SHARED builder.cpp)
set_property(TARGET SkeletonBuilder PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(SkeletonBuilder PRIVATE Undead::Skeleton)
target_link_libraries(SkeletonBuilder PRIVATE UndeadType)
target_link_libraries(SkeletonBuilder PRIVATE Undead)

cmake_minimum_required(VERSION 3.16)
project(GolemTypeRealizations)

set(CMAKE_CXX_STANDARD 20)

add_library(StoneGolem STATIC source/StoneGolem/StoneGolem.cpp)
add_library(Golem::StoneGolem ALIAS StoneGolem)

add_library(StoneGolemType STATIC source/StoneGolem/StoneGolemType.cpp)

target_link_libraries(StoneGolem Golem)
target_link_libraries(StoneGolem StoneGolemType)
target_link_libraries(StoneGolem Dungeon)
target_link_libraries(StoneGolem Floor)
target_link_libraries(StoneGolem Field)
target_link_libraries(StoneGolem Wall)

target_link_libraries(StoneGolemType GolemType)

target_include_directories(StoneGolem PUBLIC include)
target_include_directories(StoneGolemType PUBLIC include)


add_library(EtherealGolem STATIC source/EtherealGolem/EtherealGolem.cpp)
add_library(Golem::EtherealGolem ALIAS EtherealGolem)

add_library(EtherealGolemType STATIC source/EtherealGolem/EtherealGolemType.cpp)

target_link_libraries(EtherealGolem EtherealGolemType)
target_link_libraries(EtherealGolem Golem)
target_link_libraries(EtherealGolem Dungeon)
target_link_libraries(EtherealGolem Floor)
target_link_libraries(EtherealGolem Field)
target_link_libraries(EtherealGolemType GolemType)


target_include_directories(EtherealGolem PUBLIC include)
target_include_directories(EtherealGolemType PUBLIC include)


add_library(FireGolem STATIC source/FireGolem/FireGolem.cpp)
add_library(Golem::FireGolem ALIAS FireGolem)

add_library(FireGolemType STATIC source/FireGolem/FireGolemType.cpp)

target_link_libraries(FireGolem FireGolemType)
target_link_libraries(FireGolem Golem)
target_link_libraries(FireGolem Dungeon)
target_link_libraries(FireGolem Floor)
target_link_libraries(FireGolem Field)
target_link_libraries(FireGolem Magma)

target_link_libraries(FireGolemType GolemType)

target_include_directories(FireGolem PUBLIC include)
target_include_directories(FireGolemType PUBLIC include)

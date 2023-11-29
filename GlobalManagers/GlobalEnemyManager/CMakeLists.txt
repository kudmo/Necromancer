cmake_minimum_required(VERSION 3.16)
project(GlobalEnemyManager)

set(CMAKE_CXX_STANDARD 20)

add_library(GlobalEnemyManager STATIC source/GlobalEnemyManager.cpp)

target_link_libraries(GlobalEnemyManager Alive)
target_link_libraries(GlobalEnemyManager Alive::Goblin)
target_link_libraries(GlobalEnemyManager Alive::Ogr)

target_link_libraries(GlobalEnemyManager Undead)
target_link_libraries(GlobalEnemyManager Undead::Skeleton)
target_link_libraries(GlobalEnemyManager Undead::Ghoul)

target_link_libraries(GlobalEnemyManager Golem)
target_link_libraries(GlobalEnemyManager Golem::StoneGolem)
target_link_libraries(GlobalEnemyManager Golem::FireGolem)
target_link_libraries(GlobalEnemyManager Golem::EtherealGolem)

target_link_libraries(GlobalEnemyManager Dungeon)
target_link_libraries(GlobalEnemyManager Floor)
target_link_libraries(GlobalEnemyManager Field)

target_include_directories(GlobalEnemyManager PUBLIC include)
cmake_minimum_required(VERSION 3.16)
project(GlobalManagers)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(GlobalSpecialElementManager)
add_subdirectory(GlobalCoverageManager)
add_subdirectory(GlobalEnemyManager)
add_subdirectory(GlobalSkillManager)

#add_subdirectory(GlobalItemManager)
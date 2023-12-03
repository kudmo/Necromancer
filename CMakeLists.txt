cmake_minimum_required(VERSION 3.16)

project(lab3)

set(CMAKE_CXX_STANDARD 20)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-unused-parameter -std=c++2a -Wall -Wextra --coverage")

add_subdirectory(MatrixContainer)
add_subdirectory(BaseInterfaces/Interfaces)
add_subdirectory(BaseInterfaces/Object)
add_subdirectory(BaseInterfaces/Dungeon)
add_subdirectory(BaseInterfaces/Items)
add_subdirectory(BaseInterfaces/Entity)
add_subdirectory(BaseInterfaces/Enemy)
add_subdirectory(BaseInterfaces/Skill)

add_subdirectory(UserRealizations/Player)
add_subdirectory(UserRealizations/EnemyClasses)
add_subdirectory(UserRealizations/Items)
add_subdirectory(UserRealizations/Coverages)
add_subdirectory(UserRealizations/SpecialElements)
add_subdirectory(UserRealizations/EnemyTypes)
add_subdirectory(UserRealizations/Skills)
add_subdirectory(GlobalManagers)

add_subdirectory(View)

add_subdirectory(test )

#add_subdirectory(Test)
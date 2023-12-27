cmake_minimum_required(VERSION 3.16)

project(lab3)

set(CMAKE_CXX_STANDARD 20)
# -fsanitize=undefined -fsanitize=thread
# -fsanitize=address -fsanitize=leak


option(TESTING "Testing" 0)
option(MEMORY_CHECK "Memory check" 0)
option(THREADS_CHECK "Threads check" 0)
option(PROFILING "Profiling" 0)
option(ONE_THREAD "Without multi-threading" 0)

if(ONE_THREAD EQUAL 1)
    message(STATUS "One thread")
    add_compile_definitions(ONE_THREAD)
    add_definitions(-DONE_THREAD)
endif ()

if(TESTING EQUAL 1)
    message(STATUS "Tests with coverage")
    if (MEMORY_CHECK EQUAL 1)
        message(STATUS "Program with memcheck")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-unused-parameter -std=c++20 -Wall -Wextra -fsanitize=address -fsanitize=leak --coverage -g")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-unused-parameter -std=c++20 -Wall -Wextra --coverage -g")
    endif ()
    add_subdirectory(Test)
elseif (PROFILING EQUAL 1)
    message(STATUS "Profiling")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wno-unused-parameter -Wall -Wextra")
    add_subdirectory(Profiling)
else ()
    message(STATUS "With view")
    if (MEMORY_CHECK EQUAL 1)
        message(STATUS "Program with memcheck")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-unused-parameter -std=c++20 -Wall -Wextra -fsanitize=address -fsanitize=leak -g")
    elseif (THREADS_CHECK EQUAL 1)
        message(STATUS "Program with threads check")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-unused-parameter -std=c++20 -Wall -Wextra -fsanitize=thread -g")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-unused-parameter -std=c++20 -Wall -Wextra -g")
    endif ()
    add_subdirectory(View)
endif()



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

add_subdirectory(Controllers)
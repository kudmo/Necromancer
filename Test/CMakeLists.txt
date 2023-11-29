cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

project(Tests)

find_package(Catch2 2 REQUIRED)

add_executable(tests testing_main.cpp Matrix/matrix_tests.hpp)
#target_link_libraries(tests INTERFACE Matrix)
#add_library(matrix_tests STATIC Matrix/matrix_tests.hpp)


#target_link_libraries(tests matrix_tests)

target_link_libraries(tests Catch2::Catch2)

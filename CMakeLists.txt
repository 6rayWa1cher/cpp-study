cmake_minimum_required(VERSION 3.14)
project(edusandbox)

set(CMAKE_CXX_STANDARD 14)

add_executable(t1 executables/t1.cpp)

add_executable(hw1 executables/hw1_e.cpp hw1/primefunc hw1/binfunc)
add_executable(tests_hw1 catch.hpp tests/hw1.cpp hw1/primefunc)

add_executable(hw2 executables/hw2_e.cpp hw2/vectorfunc)
add_executable(tests_hw2 catch.hpp tests/hw2.cpp hw2/vectorfunc)

add_executable(hw2_1 executables/hw2_1_e.cpp hw2.1/definefun.h)
add_executable(tests_hw2_1 catch.hpp tests/hw2_1.cpp hw2.1/definefun.h)

add_executable(hw3 hw3/numcast executables/hw3.cpp hw3/stringops.cpp hw3/stringops.h hw3/sortc.cpp hw3/sortc.h)
add_executable(tests_hw3 catch.hpp tests/hw3.cpp hw3/numcast hw3/stringops.cpp hw3/stringops.h hw3/sortc.cpp hw3/sortc.h)

add_executable(hw3_1 hw3_1/functionalprog.h)
add_executable(tests_hw3_1 tests/hw3_1.cpp hw3_1/functionalprog.h)
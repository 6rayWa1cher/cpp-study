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

#add_executable(hw3_1 hw3_1/functionalprog.h)
#add_executable(tests_hw3_1 tests/hw3_1.cpp hw3_1/functionalprog.h)

add_executable(hw5 hw5/rational.cpp hw5/rational.h)
add_executable(tests_hw5 tests/hw5.cpp hw5/rational.cpp hw5/rational.h)

add_executable(hw7 hw7/dispersion.cpp hw7/dispersion.h hw7/search.cpp hw7/search.h hw7/sequence.cpp hw7/sequence.h hw7/economics.cpp hw7/economics.h hw7/datepalindromes.cpp hw7/datepalindromes.h)
add_executable(tests_hw7 hw7/dispersion.cpp hw7/dispersion.h tests/hw7.cpp hw7/search.cpp hw7/search.h hw7/sequence.cpp hw7/sequence.h hw7/economics.cpp hw7/economics.h hw7/datepalindromes.cpp hw7/datepalindromes.h)

add_executable(hw8 hw8/calc.cpp hw8/calc.h)
add_executable(tests_hw8 hw8/calc.cpp hw8/calc.h tests/hw8.cpp)

add_executable(hw9 hw9/persons.cpp hw9/persons.h executables/hw9.cpp hw9/list.cpp hw9/list.h hw9/hw9_utils.cpp hw9/hw9_utils.h)
add_executable(tests_hw9 hw9/persons.cpp hw9/persons.h hw9/list.cpp hw9/list.h tests/hw9.cpp hw9/hw9_utils.cpp hw9/hw9_utils.h)

add_executable(hw10 hw10/list2.cpp hw10/list2.h hw9/list.h hw9/list.cpp hw10/doublelinkedlist.cpp hw10/doublelinkedlist.h)
add_executable(tests_hw10 hw10/list2.cpp hw10/list2.h hw9/list.h hw9/list.cpp tests/hw10.cpp hw10/doublelinkedlist.cpp hw10/doublelinkedlist.h)
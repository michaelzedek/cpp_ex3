cmake_minimum_required(VERSION 3.8)
project(cpp_ex3)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES my_set_tester.cpp my_set.cpp my_set.h)
add_executable(cpp_ex3 ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.22)
project(parallel_prefix_sums)

set(CMAKE_CXX_STANDARD 17)

add_executable(parallel_prefix_sums src/main.cpp
        src/sequential/serial_linear.cpp
        src/sequential/serial_linear.h
        src/sequential/seq_tree.cpp
        src/parallel/p_tree.h
        src/parallel/p_block.cpp
        src/parallel/p_block.h
        src/inc.h
        src/parallel/p_tree.cpp
        src/inc.cpp)

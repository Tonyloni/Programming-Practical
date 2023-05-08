cmake_minimum_required(VERSION 3.13)
project(test VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)


add_library(my_lib STATIC argtable3.c priorityqueue.cpp dijkstra.cpp)


add_executable(graph main.cpp)

target_link_libraries(graph PRIVATE my_lib)


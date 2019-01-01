cmake_minimum_required(VERSION 3.12)
project(ThreadPool)

link_libraries(pthread)

set(CMAKE_CXX_STANDARD 14)

add_executable(ThreadPool main.cpp ThreadPool.cpp ThreadPool.h)
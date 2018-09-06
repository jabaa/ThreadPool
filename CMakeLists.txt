cmake_minimum_required(VERSION 3.5.1)
project(ThreadPool)

set(CMAKE_CXX_STANDARD 11)

set(BUILD_EXAMPLES False CACHE BOOL "Build examples")

include_directories(include)
add_library(ThreadPool src/ThreadPool.cpp include/ThreadPool.h)

if (BUILD_EXAMPLES)
    find_package(Threads REQUIRED)
    add_executable(example1 examples/example1.cpp)
    target_link_libraries(example1 ThreadPool ${CMAKE_THREAD_LIBS_INIT})
endif()

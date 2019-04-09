cmake_minimum_required(VERSION 3.5.1)
project(ThreadPoolTest)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
CONAN_BASIC_SETUP(TARGETS)

find_package(Threads REQUIRED)
add_executable(example1 ../examples/example1.cpp)
target_link_libraries(example1 CONAN_PKG::ThreadPool ${CMAKE_THREAD_LIBS_INIT})

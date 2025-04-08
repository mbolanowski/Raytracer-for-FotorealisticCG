cmake_minimum_required(VERSION 3.27)
project(2)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "src/*")
add_executable(2 ${SOURCES})

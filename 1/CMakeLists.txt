cmake_minimum_required(VERSION 3.27)
project(2)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "src/*")
add_executable(2 ${SOURCES}
        src/rtx/Material.h
        src/rtx/Light.h
        src/rtx/PointLight.h
        src/foto_tasks/task3.cpp)

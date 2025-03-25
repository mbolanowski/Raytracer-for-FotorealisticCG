cmake_minimum_required(VERSION 3.30)
project(2)

set(CMAKE_CXX_STANDARD 20)

add_executable(2 main.cpp
        Vector.h
        Point.h
        Point.cpp
        Vector.cpp
        Ray.h
        Sphere.h
        Sphere.cpp
        Ray.cpp
        Plane.h
        Plane.cpp
        Triangle.h
        Triangle.cpp
        Matrix.h
        Matrix.cpp
        Quaternion.h
        Quaternion.cpp)

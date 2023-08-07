cmake_minimum_required(VERSION 3.26)
project(weegrad)

set(CMAKE_CXX_STANDARD 17)

add_executable(weegrad main.cpp
        linearalg/matrix.cpp
        linearalg/matrix.h
        linearalg/ops.cpp
        linearalg/ops.h)

cmake_minimum_required(VERSION 3.2)
project(weegrad)

set(CMAKE_CXX_STANDARD 17)

add_executable(weegrad main.cpp
        linearalg/matrix.cpp
        linearalg/matrix.h
        linearalg/ops.cpp
        linearalg/ops.h
        net/nn.cpp
        net/nn.h
        net/dense.cpp
        net/dense.h
        tests/tests.cpp
        tests/tests.h)

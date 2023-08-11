cmake_minimum_required(VERSION 3.2)
project(weegrad)

set(CMAKE_CXX_STANDARD 17)

add_executable(weegrad main.cpp
        linearalg/Matrix.cpp
        linearalg/Matrix.h
        linearalg/Ops.cpp
        linearalg/Ops.h
        net/Net.cpp
        net/Net.h
        net/Dense.cpp
        net/Dense.h
        tests/tests.cpp
        tests/tests.h
        net/Layer.cpp
        net/Layer.h
        net/ReLU.cpp
        net/ReLU.h)

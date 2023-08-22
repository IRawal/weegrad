cmake_minimum_required(VERSION 3.23)
project(weegrad)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

add_executable(weegrad main.cpp
        linearalg/Matrix.cpp
        linearalg/Matrix.h
        linearalg/Ops.cpp
        linearalg/Ops.h
        net/Net.cpp
        net/Net.h
        net/layers/Dense.cpp
        net/layers/Dense.h
        tests/tests.cpp
        tests/tests.h
        net/Layer.cpp
        net/Layer.h
        net/layers/ReLU.cpp
        net/layers/ReLU.h
        net/LayerType.cpp
        net/LayerType.h
        net/ActivationLayer.cpp
        net/ActivationLayer.h
        net/layers/Sigmoid.cpp
        net/layers/Sigmoid.h)

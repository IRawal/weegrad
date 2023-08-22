//
// Created by isha on 8/8/23.
//

#include "tests.h"
#include "../net/layers/Dense.h"
#include "../net/Net.h"
#include "../net/layers/ReLU.h"
#include "../net/layers/Sigmoid.h"
#include "../linearalg/Ops.h"
#include "../net/layers/Tanh.h"

#include <cstdio>
#include <ctime>
#include <chrono>
#include <iostream>

void test_mult() {
    long start = time(nullptr);
    Matrix *m1 = new Matrix(1024, 1024);
    m1->fill(1);
    Matrix *m2 = new Matrix(1024, 1024);
    m2->fill(1);
    //Ops::matmul_fast(m1, m2);
    printf("Took %li seconds\n",  time(nullptr) - start);
}
void addition_nn_test() {
    int depth = 5;
    Layer** layers = static_cast<Layer**>(malloc(sizeof(Layer*) * depth));

    layers[0] = new Dense(2, 2);
    layers[1] = new Sigmoid();
    layers[2] = new Dense(2, 2);
    layers[3] = new Sigmoid();
    layers[4] = new Dense(2, 1);

    Net net = Net(layers, depth);

    int examples = 8;

    Matrix** xs = static_cast<Matrix**>(malloc(sizeof(Matrix*) * examples));
    Matrix** ys = static_cast<Matrix**>(malloc(sizeof(Matrix*) * examples));

    xs[0] = new Matrix(2, 1);
    xs[0]->elements[0][0] = 0.1;
    xs[0]->elements[1][0] = 0.2;
    xs[1] = new Matrix(2, 1);
    xs[1]->elements[0][0] = 0.5;
    xs[1]->elements[1][0] = 0.7;
    xs[2] = new Matrix(2, 1);
    xs[2]->elements[0][0] = 0.8;
    xs[2]->elements[1][0] = 0.4;
    xs[3] = new Matrix(2, 1);
    xs[3]->elements[0][0] = 0.11;
    xs[3]->elements[1][0] = 0.14;
    xs[4] = new Matrix(2, 1);
    xs[4]->elements[0][0] = 0.6;
    xs[4]->elements[1][0] = 0.23;
    xs[5] = new Matrix(2, 1);
    xs[5]->elements[0][0] = 0.3;
    xs[5]->elements[1][0] = 0.63;
    xs[6] = new Matrix(2, 1);
    xs[6]->elements[0][0] = 0.5;
    xs[6]->elements[1][0] = 0.29;
    xs[7] = new Matrix(2, 1);
    xs[7]->elements[0][0] = 0.1;
    xs[7]->elements[1][0] = 0.25;

    ys[0] = new Matrix(1, 1);
    ys[0]->elements[0][0] = 0.1+0.2;
    ys[1] = new Matrix(1, 1);
    ys[1]->elements[0][0] = 0.5+0.7;
    ys[2] = new Matrix(1, 1);
    ys[2]->elements[0][0] = 0.8+0.4;
    ys[3] = new Matrix(1, 1);
    ys[3]->elements[0][0] = 0.11+0.14;
    ys[4] = new Matrix(1, 1);
    ys[4]->elements[0][0] = 0.6+0.23;
    ys[5] = new Matrix(1, 1);
    ys[5]->elements[0][0] = 0.3+0.63;
    ys[6] = new Matrix(1, 1);
    ys[6]->elements[0][0] = 0.5+0.29;
    ys[7] = new Matrix(1, 1);
    ys[7]->elements[0][0] = 0.1+0.25;

    net.train(xs, ys, examples, 0.01, 100000);

    Matrix* input = new Matrix(2, 1);
    input->elements[0][0] = 1.11;
    input->elements[1][0] = 0.14;

    printf("%s\n", "Input:" );
    input->print();
    printf("%s", "Output: ");

    net.forward(input)->print();
}
void test_addition() {
    Matrix* m1 = new Matrix(1, 1000);
    Matrix* m2 = new Matrix(1, 1000);
    m2->fill(1);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        m1->add_fast(m2);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    m1->print();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << "ms\n";
}
void test_sum() {
    Matrix* m1 = new Matrix(1, 101);
    m1->fill(1);
    float a[3] = {1.f, 2.f, 3.f};
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        Ops::vec_sum_fast(a, 3);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "Fast took " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << "ms\n";
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        m1->sum();
    }
    finish = std::chrono::high_resolution_clock::now();
    std::cout << "Slow took " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << "ms\n";
}
//void test_matmul() {
//    Matrix* m1 = new Matrix(1, 101);
//    Matrix* m2 = new Matrix(101, 1);
//    m1->fill(1);
//    m2->fill(2);
//
//    auto start = std::chrono::high_resolution_clock::now();
//    for (int i = 0; i < 10000; i++) {
//        Ops::matmul_fast(m1, m2);
//    }
//    auto finish = std::chrono::high_resolution_clock::now();
//    std::cout << "Fast took " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << "ms\n";
//    start = std::chrono::high_resolution_clock::now();
//    for (int i = 0; i < 10000; i++) {
//        Ops::matmul(m1, m2);
//    }
//    finish = std::chrono::high_resolution_clock::now();
//    std::cout << "Slow took " << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << "ms\n";
//}
void test_convergence() {
    int depth = 5;
    Layer** layers = static_cast<Layer**>(malloc(sizeof(Layer*) * depth));

    layers[0] = new Dense(2, 2);
    layers[1] = new Sigmoid();
    layers[2] = new Dense(2, 2);
    layers[3] = new Sigmoid();
    layers[4] = new Dense(2, 1);

    Net net = Net(layers, depth);

    int examples = 1;

    Matrix** xs = static_cast<Matrix**>(malloc(sizeof(Matrix*) * examples));
    Matrix** ys = static_cast<Matrix**>(malloc(sizeof(Matrix*) * examples));

    xs[0] = new Matrix(1, 2);
    xs[0]->elements[0][0] = 0.1;
    xs[0]->elements[0][1] = 0.2;

    ys[0] = new Matrix(1, 1);
    ys[0]->elements[0][0] = 0.1+0.2;

    net.train(xs, ys, examples, 0.01, 1000);
    net.forward(xs[0])->print();
}
void test_dense() {
    Dense layer = Dense(2, 1);
    Matrix vec = Matrix(1, 2);
    layer.forward(&vec)->print();
}
void test_nn_mult() {
    int depth = 7;
    Layer** layers = static_cast<Layer**>(malloc(sizeof(Layer*) * depth));

    layers[0] = new Dense(2, 2);
    layers[1] = new Tanh();
    layers[2] = new Dense(2, 5);
    layers[3] = new Tanh();
    layers[4] = new Dense(5, 5);
    layers[5] = new Tanh();
    layers[6] = new Dense(5, 1);

    Net net = Net(layers, depth);

    int examples = 8;

    Matrix** xs = static_cast<Matrix**>(malloc(sizeof(Matrix*) * examples));
    Matrix** ys = static_cast<Matrix**>(malloc(sizeof(Matrix*) * examples));

    xs[0] = new Matrix(1, 2);
    xs[0]->elements[0][0] = 0.1;
    xs[0]->elements[0][1] = 0.2;
    xs[1] = new Matrix(1, 2);
    xs[1]->elements[0][0] = 0.5;
    xs[1]->elements[0][1] = 0.7;
    xs[2] = new Matrix(1, 2);
    xs[2]->elements[0][0] = 0.8;
    xs[2]->elements[0][1] = 0.4;
    xs[3] = new Matrix(1, 2);
    xs[3]->elements[0][0] = 0.11;
    xs[3]->elements[0][1] = 0.14;
    xs[4] = new Matrix(1, 2);
    xs[4]->elements[0][0] = 0.6;
    xs[4]->elements[0][1] = 0.23;
    xs[5] = new Matrix(1, 2);
    xs[5]->elements[0][0] = 0.3;
    xs[5]->elements[0][1] = 0.63;
    xs[6] = new Matrix(1, 2);
    xs[6]->elements[0][0] = 0.5;
    xs[6]->elements[0][1] = 0.29;
    xs[7] = new Matrix(1, 2);
    xs[7]->elements[0][0] = 0.1;
    xs[7]->elements[0][1] = 0.25;

    ys[0] = new Matrix(1, 1);
    ys[0]->elements[0][0] = 0.1*0.2;
    ys[1] = new Matrix(1, 1);
    ys[1]->elements[0][0] = 0.5*0.7;
    ys[2] = new Matrix(1, 1);
    ys[2]->elements[0][0] = 0.8*0.4;
    ys[3] = new Matrix(1, 1);
    ys[3]->elements[0][0] = 0.11*0.14;
    ys[4] = new Matrix(1, 1);
    ys[4]->elements[0][0] = 0.6*0.23;
    ys[5] = new Matrix(1, 1);
    ys[5]->elements[0][0] = 0.3*0.63;
    ys[6] = new Matrix(1, 1);
    ys[6]->elements[0][0] = 0.5*0.29;
    ys[7] = new Matrix(1, 1);
    ys[7]->elements[0][0] = 0.1*0.25;


    net.train(xs, ys, examples, 0.001, 30000);

    Matrix** tests = static_cast<Matrix**>(malloc(sizeof(Matrix*) * examples));

    tests[0] = new Matrix(1, 2);
    tests[0]->elements[0][0] = 0.2;
    tests[0]->elements[0][1] = 0.2;

    tests[1] = new Matrix(1, 2);
    tests[1]->elements[0][0] = 0.6;
    tests[1]->elements[0][1] = 0.3;

    tests[2] = new Matrix(1, 2);
    tests[2]->elements[0][0] = 0.21;
    tests[2]->elements[0][1] = 0.34;

    tests[3] = new Matrix(1, 2);
    tests[3]->elements[0][0] = 0.4;
    tests[3]->elements[0][1] = 0.8;

    for (int i = 0; i < examples; i++) {
        net.forward(tests[i])->print();
    }
}
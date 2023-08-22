#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <filesystem>

#include "linearalg/Matrix.h"
#include "linearalg/Ops.h"
#include "net/Net.h"
#include "net/layers/ReLU.h"
#include "net/layers/Sigmoid.h"

#include "tests/tests.h"

int main() {
    test_addition();

//    Matrix** xs = static_cast<Matrix**>(malloc(sizeof(Matrix*) * 1000));
//    Matrix** ys = static_cast<Matrix**>(malloc(sizeof(Matrix*) * 1000));
//
//    std::string path = "../data/out/0";
//    int i = 0;
//    for (const auto & entry : std::filesystem::directory_iterator(path)) {
//        std::ifstream input(entry.path(), std::ios::binary);
//
//        Matrix *img = new Matrix(1, 28 * 28);
//        for (int j = 0; j < 28 * 28; j++) {
//            img->elements[0][j] = input.get() / 255.;
//        }
//        xs[i] = img;
//        ys[i] = new Matrix(1, 1);
//        i++;
//    }
//
//    int depth = 5;
//    Layer** layers = static_cast<Layer**>(malloc(sizeof(Layer*) * depth));
//    int insize = 28 * 28;
//
//    layers[0] = new Dense(insize, insize);
//    layers[1] = new ReLU();
//    layers[2] = new Dense(insize, insize);
//    layers[3] = new ReLU();
//    layers[4] = new Dense(insize, 1);
//
//    Net net = Net(layers, depth);
//    auto start = std::chrono::high_resolution_clock::now();
//    net.train(xs, ys, 100, 0.001, 1);
//    auto finish = std::chrono::high_resolution_clock::now();
//    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << "ms\n";
    //net.forward(xs[101])->print();

    return 0;
}

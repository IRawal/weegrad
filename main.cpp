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
    Matrix** xs = static_cast<Matrix**>(malloc(sizeof(Matrix*) * 1000));
    Matrix** ys = static_cast<Matrix**>(malloc(sizeof(Matrix*) * 1000));
    std::string path = "../data/out/0";
    int i = 0;
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        std::ifstream input(entry.path(), std::ios::binary);

        Matrix *img = new Matrix(28 * 28, 1);
        for (int i = 0; i < 28 * 28; i++) {
            img->elements[i][0] = input.get() / 255.;
        }
        xs[i] = img;
        ys[i] = new Matrix(1, 1);
        i++;
    }

    int depth = 5;
    Layer** layers = static_cast<Layer**>(malloc(sizeof(Layer*) * depth));
    int insize = 28 * 28;

    layers[0] = new Dense(insize, insize);
    layers[1] = new Sigmoid();
    layers[2] = new Dense(insize, insize);
    layers[3] = new Sigmoid();
    layers[4] = new Dense(insize, 1);

    //Ops::shuffle(xs[0], xs[0]);
    //xs[0]->print();

    Net net = Net(layers, depth);
    net.train(xs, ys, 10, 0.001, 30);
    net.forward(xs[0])->print();
    return 0;
}

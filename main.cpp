#include <iostream>
#include <vector>

#include "linearalg/Matrix.h"
#include "linearalg/Ops.h"
#include "net/Net.h"
#include "net/ReLU.h"

int main() {
    int depth = 5;
    Layer** layers = static_cast<Layer**>(malloc(sizeof(Layer*) * depth));

    layers[0] = new Dense(1, 2);
    layers[1] = new ReLU();
    layers[2] = new Dense(2, 10);
    layers[3] = new ReLU();
    layers[4] = new Dense(10, 1);

    Net net = Net(layers, depth);

    Matrix* in = new Matrix(1, 1);
    in->elements[0][0] = 1.3;

    Matrix* expected = (new Matrix(1, 1))->broadcast([](double d) -> double {return 2;});
    net.train(in, expected, 0.001, 10000);
    net.forward(in)->print();

    return 0;
}

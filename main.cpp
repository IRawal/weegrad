#include <iostream>
#include <vector>

#include "linearalg/Matrix.h"
#include "linearalg/Ops.h"
#include "net/Net.h"
#include "net/ReLU.h"

int main() {
    int depth = 5;
    Layer** layers = static_cast<Layer**>(malloc(sizeof(Layer*) * depth));

    layers[0] = new Dense(1, 3);
    layers[1] = new ReLU();
    layers[2] = new Dense(3, 1);
    layers[3] = new ReLU();
    layers[4] = new Dense(1, 1);

    Net net = Net(layers, depth);

    Matrix in = Matrix(1, 1);
    in.elements[0][0] = 1.3;

    Matrix* expected = Matrix(1, 1).broadcast([](double d) -> double {return 2;});
    net.train(&in, expected, 0.1);
    net.forward(&in)->print();

    return 0;
}

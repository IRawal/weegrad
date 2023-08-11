#include <iostream>
#include <vector>

#include "linearalg/Matrix.h"
#include "linearalg/Ops.h"
#include "net/Net.h"
#include "net/ReLU.h"

int main() {
    int depth = 1;
    //Layer* layers = static_cast<Layer*>(malloc(sizeof(Layer) * depth));
    //layers[0] =

    std::vector<Layer*> layers;
    layers.push_back(new Dense(1, 1));
    //layers.push_back(new ReLU());

    Net net = Net(layers, depth);

    Matrix in = Matrix(1, 1);
    in.elements[0][0] = 0;
    Matrix* expected = Matrix(1, 1).broadcast([](double d) -> double {return 2;});
    net.train(&in, expected);
    net.forward(&in)->print();

    return 0;
}

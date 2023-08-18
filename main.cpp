#include <iostream>
#include <vector>

#include "linearalg/Matrix.h"
#include "linearalg/Ops.h"
#include "net/Net.h"
#include "net/ReLU.h"

int main() {
    int depth = 7;
    Layer** layers = static_cast<Layer**>(malloc(sizeof(Layer*) * depth));

    layers[0] = new Dense(2, 5);
    layers[1] = new ReLU();
    layers[2] = new Dense(5, 5);
    layers[3] = new ReLU();
    layers[4] = new Dense(5, 2);
    layers[5] = new ReLU();
    layers[6] = new Dense(2, 1);

    Net net = Net(layers, depth);

    int examples = 5;

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

    net.train(xs, ys, examples, 0.01, 10000);

    Matrix* input = new Matrix(2, 1);
    input->elements[0][0] = 0.4;
    input->elements[1][0] = 0.2;

    printf("%s\n", "Input:" );
    xs[0]->print();
    printf("%s", "Output: ");

    net.forward(input)->print();

    return 0;
}

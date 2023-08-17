#include <iostream>
#include <vector>

#include "linearalg/Matrix.h"
#include "linearalg/Ops.h"
#include "net/Net.h"
#include "net/ReLU.h"

int main() {
    int depth = 5;
    Layer** layers = static_cast<Layer**>(malloc(sizeof(Layer*) * depth));

    layers[0] = new Dense(2, 3);
    layers[1] = new ReLU();
    layers[2] = new Dense(3, 3);
    layers[3] = new ReLU();
    layers[4] = new Dense(3, 1);

    Net net = Net(layers, depth);

    int examples = 5;

    Matrix** xs = static_cast<Matrix**>(malloc(sizeof(Matrix*) * examples));
    Matrix** ys = static_cast<Matrix**>(malloc(sizeof(Matrix*) * examples));


    xs[0] = new Matrix(1, 2);
    xs[0]->elements[0][0] = 2;
    xs[0]->elements[0][1] = 3;
    xs[1] = new Matrix(1, 2);
    xs[1]->elements[0][0] = 4;
    xs[1]->elements[0][1] = 6;
    xs[2] = new Matrix(1, 2);
    xs[2]->elements[0][0] = 8;
    xs[2]->elements[0][1] = 4;
    xs[3] = new Matrix(1, 2);
    xs[3]->elements[0][0] = 7;
    xs[3]->elements[0][1] = 9;
    xs[4] = new Matrix(1, 2);
    xs[4]->elements[0][0] = 12;
    xs[4]->elements[0][1] = 5;

    ys[0] = new Matrix(1, 1);
    ys[0]->elements[0][0] = 2 * 3;
    ys[1] = new Matrix(1, 1);
    ys[1]->elements[0][0] = 4 * 6;
    ys[2] = new Matrix(1, 1);
    ys[2]->elements[0][0] = 8 * 4;
    ys[3] = new Matrix(1, 1);
    ys[3]->elements[0][0] = 7 * 9;
    ys[4] = new Matrix(1, 1);
    ys[4]->elements[0][0] = 12 * 5;

    net.train(xs, ys, examples, 0.00001, 1000);

    Matrix* input = (new Matrix(1, 2));
    input->elements[0][0] = 3;
    input->elements[0][1] = 14;

    printf("%s", "Input:" );
    input->print();
    printf("%s", "Output: ");

    net.forward(input)->print();

    return 0;
}

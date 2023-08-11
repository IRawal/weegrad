#include <iostream>

#include "linearalg/matrix.h"
#include "linearalg/ops.h"
#include "net/nn.h"

int main() {
    int depth = 1;
    dense* layers = static_cast<dense*>(malloc(sizeof(dense) * depth));
    layers[0] = dense(1, 1);
    nn net = nn(layers, depth);

    matrix in = matrix(1, 1);
    in.elements[0][0] = 1;

    net.train(&in, new matrix(1, 1));
    net.forward(&in, &nn::relu).print();

    return 0;
}

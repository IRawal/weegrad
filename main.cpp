#include <iostream>

#include "linearalg/matrix.h"
#include "linearalg/ops.h"
#include "net/nn.h"

int main() {
    int depth = 2;
    dense* layers = static_cast<dense*>(malloc(sizeof(dense) * depth));
    layers[0] = dense(2, 2);
    layers[1] = dense(2, 1);
    nn net = nn(layers, depth);

    matrix in = matrix(1, 2);

    //net.train(&in, new matrix(1, 1));


    return 0;
}

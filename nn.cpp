//
// Created by isha on 8/7/23.
//

#include "nn.h"
#include "linearalg/matrix.h"
#include "linearalg/ops.h"

#include <cstdlib>

matrix* net;
int depth;

nn::nn(matrix* layers, int netDepth) {
    net = layers;
    depth = netDepth;
    for (int i = 0; i < depth; i++) {
        layers[i].randomize();
    }
}
double relu(double d) {
    if (d < 0)
        return 0;
    else
        return d;
}
matrix nn::forward(matrix in) {
    matrix tmp = ops::multiply(in, net[0]);
    // Hidden layers
    for (int i = 1; i < depth - 1; i++) {
        tmp = ops::multiply(tmp, net[i]);
        tmp.broadcast(&relu);
    }
    // Output
    tmp = ops::multiply(tmp, net[depth - 1]);
    return tmp;
}


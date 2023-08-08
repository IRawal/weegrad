#include <iostream>

#include "linearalg/matrix.h"
#include "linearalg/ops.h"
#include "nn.h"

int main() {

        int depth = 2;
        matrix* layers = static_cast<matrix*>(malloc(sizeof(matrix) * depth));

        layers[0] = matrix(2, 2);
        layers[1] = matrix(2, 1);

        nn net = nn(layers, depth);
        matrix in = matrix(1, 2);
        in.randomize();
        net.forward(in).print();

//    matrix m1 = matrix(1, 2);
//    matrix m2 = matrix(2, 2);
//    ops::multiply(m1, m2).print();
    return 0;
}

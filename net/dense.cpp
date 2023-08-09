//
// Created by isha on 8/8/23.
//

#include "dense.h"
#include "../linearalg/matrix.h"
#include "../linearalg/ops.h"

matrix* weights;
matrix* biases;

dense::dense(int inLen, int outLen) {
    weights = new matrix(inLen, outLen);
    biases = new matrix(1, outLen);
    weights->randomize();
    biases->randomize();
}
matrix dense::forward(matrix* in) {
    matrix out = ops::multiply(in, weights);
    out = ops::add(&out, biases);
    return out;
}

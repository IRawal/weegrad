//
// Created by isha on 8/8/23.
//

#include "Dense.h"
#include "../linearalg/Matrix.h"
#include "../linearalg/Ops.h"

Matrix* weights;
Matrix* biases;

Dense::Dense(int inLen, int outLen) {
    this->type = LayerType::Dense;
    weights = new Matrix(inLen, outLen);
    biases = new Matrix(1, outLen);
    weights->randomize();
    biases->randomize();
}
Matrix* Dense::forward(Matrix* in) {
    Matrix* out = Ops::multiply(in, weights);
    out = Ops::add(out, biases);
    return out;
}

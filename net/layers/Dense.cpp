//
// Created by isha on 8/8/23.
//

#include "Dense.h"
#include "../../linearalg/Matrix.h"
#include "../../linearalg/Ops.h"
#include <random>

Matrix* weights;
Matrix* biases;

Dense::Dense(int inLen, int outLen) {
    this->type = LayerType::Dense;
    weights = new Matrix(outLen, inLen);
    biases = new Matrix(outLen, 1);
    std::normal_distribution dist = std::normal_distribution<double>(0, sqrt(2.0 / inLen));
    std::random_device rd{};
    std::mt19937 gen{rd()};

    weights->broadcast([&dist, &gen](double d) {return dist(gen);});
}
Matrix* Dense::forward(Matrix* in) {
    Matrix* out = Ops::matmul(weights, in);
    out->add(biases);
    return out;
}

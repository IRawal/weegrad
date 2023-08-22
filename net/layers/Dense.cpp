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
    weights = new Matrix(inLen, outLen);
    biases = new Matrix(1, outLen);

    std::normal_distribution dist = std::normal_distribution<float>(0, sqrtf32(2.0f / inLen));
    std::random_device rd{};
    std::mt19937 gen{rd()};

    weights->broadcast([&dist, &gen](float d) {return dist(gen);});
}
Matrix* Dense::forward(Matrix* in) {
    Matrix* out = Ops::matmul(in, weights);
    out->add_fast(biases);
    return out;
}

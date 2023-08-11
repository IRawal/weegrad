//
// Created by isha on 8/7/23.
//

#include "nn.h"
#include "dense.h"

#include "../linearalg/matrix.h"
#include "../linearalg/ops.h"

#include <cmath>
#include <cstdlib>
#include <cstdio>

dense* layers;
matrix* neurons;
int depth;

nn::nn(dense *layers, int depth) {
    this->layers = layers;
    this->depth = depth;
    neurons = static_cast<matrix*>(malloc(sizeof(matrix) * (depth + 1)));
}
double nn::relu(double x) {
    if (x < 0)
        return 0;
    else
        return x;
}
double nn::drelu(double x) {
    if (x < 0)
        return 0;
    else
        return 1;
}
double loss(matrix *in, matrix *expected) {
    if (in->rows != expected->rows || in->cols != expected->cols)
        exit(-1);
    double loss = 0;
    for (int i = 0; i < in->rows; i++) {
        for (int j = 0; j < in->cols; j++) {
            loss += pow(in->elements[i][j] - expected->elements[i][j], 2);
        }
    }
    return loss / (in->rows * in->cols);
}
matrix nn::forward(matrix *in, double (*fn)(double)) {
    // Load input into network
    neurons[0] = *in;
    // Apply each layer and activation fn
    for (int i = 0; i < depth; i++) {
        neurons[i + 1] = layers[i].forward(&neurons[i]);
        neurons[i + 1].broadcast(fn);
    }
    // Output layer
    neurons[depth] = layers[depth - 1].forward(&neurons[depth - 1]);
    return neurons[depth];
}
matrix nn::train(matrix *in, matrix *expected) {
    matrix out = forward(in, &relu);
    double mse = loss(&out, expected);
    matrix dcda = ops::subtract(&neurons[depth], expected).broadcast([](double d){return d * 2;}); // dCost/dOut = 2(y - yhat)
    matrix dadz = dcda.clone().broadcast(&drelu);
    matrix dzdw = *in;
    dcdw =
}


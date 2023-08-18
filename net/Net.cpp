//
// Created by isha on 8/7/23.
//

#include "Net.h"
#include "Dense.h"

#include "../linearalg/Matrix.h"
#include "../linearalg/Ops.h"
#include "ReLU.h"

#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <utility>
#include <vector>

Layer** layers;
Matrix* neurons;
int depth;

Net::Net(Layer** layers, int depth) {
    this->layers = layers;
    this->depth = depth;
    neurons = static_cast<Matrix*>(malloc(sizeof(Matrix) * (depth + 1))); // One output for each layer + input layer
}
double loss(Matrix *in, Matrix *expected) {
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
Matrix* Net::forward(Matrix *in) {
    // Load input into network
    neurons[0] = *in;
    // Apply each Layer
    for (int i = 0; i < depth; i++) {
        neurons[i + 1] = *layers[i]->forward(&neurons[i]);
    }
    return &neurons[depth];
}
void Net::train(Matrix **xs, Matrix **ys, int examples, double rate, int epochs) {
    for (int eps = 0; eps < epochs; eps++) {

        for (int i = 0; i < examples; i++) {
            Matrix* newIn = xs[i]->copy();

            Matrix* out = forward(newIn);
            printf("Loss: %f\n", loss(out, ys[i]));
            step(ys[i], 0.001);
        }
    }
}

void Net::step(Matrix *expected, double rate) {
    Matrix* dcdb = Ops::subtract(&neurons[depth], expected); // dCost/dOut ~= (y - yhat);
    for (int i = depth - 1; i >= 0; i--) {
        Layer* layer = layers[i];

        if (layer->type == LayerType::Dense) {
            Dense* dense = ((Dense *) layer);

            Matrix* dcdw = Ops::matmul(dcdb, neurons[i].copy()->transpose());

            Matrix* bsum = Ops::rowSum(dcdb);

            dense->weights = Ops::subtract(dense->weights, dcdw->broadcast([&rate](double d) -> double {return d * rate;}));
            dense->biases = Ops::subtract(dense->biases, bsum->broadcast([&rate](double d) -> double {return d * rate;}));

            dcdb = Ops::matmul(dense->weights->copy()->transpose(), dcdb);
        }
        else if (layer->type == LayerType::ActivationFn) {
            dcdb = Ops::schur(dcdb, neurons[i].copy()->broadcast([&layer](double d){return ((ActivationLayer*) layer)->dfdx(d);}));
        }
    }
}



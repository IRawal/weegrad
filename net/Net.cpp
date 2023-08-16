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
void Net::train(Matrix *in, Matrix *expected, double rate, int epochs) {
    for (int eps = 0; eps < epochs; eps++) {
        Matrix* newIn = in->clone();
        Matrix* out = forward(newIn);

        Matrix* dcdb = Ops::subtract(&neurons[depth], expected); // dCost/dOut ~= (y - yhat);

        for (int i = depth - 1; i >= 0; i--) {
            Layer* layer = layers[i];

            if (layer->type == LayerType::Dense) {
                Dense* dense = ((Dense *) layer);

                Matrix* dcdw = Ops::matmul(dcdb->transpose(), &neurons[i]);

                Matrix* dcdb_t = dcdb->clone()->transpose();

                ((Dense *) layer)->weights = Ops::subtract(dense->weights, dcdw->broadcast([&rate](double d) -> double {return d * rate;})->transpose());
                ((Dense *) layer)->biases = Ops::subtract(dense->biases, dcdb_t->broadcast([&rate](double d) -> double {return d * rate;}));

                delete(dcdw);

                delete(dcdb_t);

                Matrix* new_dcdb = Ops::matmul(dense->weights, dcdb);

                delete(dcdb);

                dcdb = new_dcdb;
            }
            else if (layer->type == LayerType::ActivationFn) {
                dcdb = Ops::schur(dcdb->transpose(), neurons[i].broadcast(&ReLU::drelu));
                //dcdb *= neurons[i].broadcast(&ReLU::drelu);
            }
        }
    }
}


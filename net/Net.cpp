//
// Created by isha on 8/7/23.
//

#include "Net.h"
#include "layers/Dense.h"

#include "../linearalg/Matrix.h"
#include "../linearalg/Ops.h"
#include "layers/ReLU.h"

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
    neurons = static_cast<Matrix**>(malloc(sizeof(Matrix*) * (depth + 1))); // One output for each layer + input layer
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
    neurons[0] = in;
    // Apply each Layer
    for (int i = 0; i < depth; i++) {
        neurons[i + 1] = layers[i]->forward(neurons[i]);
    }
    return neurons[depth];
}
void Net::train(Matrix **xs, Matrix **ys, int examples, double rate, int epochs) {
    for (int eps = 0; eps < epochs; eps++) {
        Ops::shuffle(xs, ys, examples);
        for (int i = 0; i < examples; i++) {
            Matrix* in = xs[i]->copy();
            Matrix* out = forward(in);
            printf("Loss: %f\n", loss(out, ys[i]));
            step(ys[i], rate);

            for (int j = 0; j <= depth; j++) {
                delete neurons[j];
            }
        }
        printf("Epoch: %i\n", eps + 1);
    }
}
void Net::step(Matrix *expected, double rate) {
    Matrix* neuron_copy = neurons[depth]->copy();
    Matrix* dcdb = neuron_copy->subtract(expected); // dCost/dOut ~= (y - yhat);
    for (int i = depth - 1; i >= 0; i--) {
        Layer* layer = layers[i];

        if (layer->type == LayerType::Dense) {
            Dense* dense = ((Dense *) layer);

            Matrix* neurons_t = neurons[i]->copy()->transpose();
            Matrix* dcdw = Ops::matmul(dcdb, neurons_t);

            delete neurons_t;

            Matrix* bsum = Ops::rowSum(dcdb);

            dense->weights = dense->weights->subtract(dcdw->scale(rate));
            dense->biases = dense->biases->subtract(bsum->scale(rate));

            delete dcdw;
            delete bsum;

            Matrix* weights_t = dense->weights->copy()->transpose();
            Matrix* old_dcdb = dcdb;
            dcdb = Ops::matmul(weights_t, dcdb);

            delete old_dcdb;
            delete weights_t;
        }
        else if (layer->type == LayerType::ActivationFn) {
            //Matrix* activated = neurons[i].copy()->activate(((ActivationLayer*) layer));
            Matrix* activated = neurons[i]->copy()->broadcast([&layer](double d){return ((ActivationLayer*) layer)->dfdx(d);});

            dcdb->shur(activated);

            delete activated;
        }
    }
    delete dcdb;
}



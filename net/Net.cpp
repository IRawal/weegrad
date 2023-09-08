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

Net::Net(Layer** layers, int depth) {
    this->layers = layers;
    this->depth = depth;
    neurons = static_cast<Matrix**>(malloc(sizeof(Matrix*) * (depth + 1))); // One output for each layer + input layer
    for (int i = 0; i < depth; i++) {
        Layer* layer = layers[i];
        if (layer->type != LayerType::Dense)
            continue;
        auto dense = (Dense*) layer;
        for (int k = 0; k < dense->weights->rows; k++) {
            for (int j = 0; j < dense->weights->cols; j++) {
                this->param_count++;
            }
        }
        for (int k = 0; k < dense->biases->rows; k++) {
            for (int j = 0; j < dense->biases->cols; j++) {
                this->param_count++;
            }
        }
    }
}
float loss(Matrix *in, Matrix *expected) {
    if (in->rows != expected->rows || in->cols != expected->cols)
        exit(-1);
    float loss = 0;
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
// Stochastic gradient descent
void Net::train(Matrix **xs, Matrix **ys, int examples, float rate, int epochs) {
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
float** Net::get_params() {
    auto params = static_cast<float**>(malloc(sizeof(float*) * this->param_count));
    int param_ind = 0;
    for (int i = 0; i < depth; i++) {
        Layer* layer = layers[i];
        if (layer->type != LayerType::Dense)
            continue;
        auto dense = (Dense*) layer;
        for (int k = 0; k < dense->weights->rows; k++) {
            for (int j = 0; j < dense->weights->cols; j++) {
                params[param_ind] = dense->weights->elements[k] + j;
                param_ind++;
            }
        }
        for (int k = 0; k < dense->biases->rows; k++) {
            for (int j = 0; j < dense->biases->cols; j++) {
                params[param_ind] = dense->biases->elements[k] + j;
                param_ind++;
            }
        }
    }
    return params;
}
void Net::step(Matrix *expected, float rate) {
    Matrix* neuron_copy = neurons[depth]->copy();
    Matrix* dcdb = neuron_copy->subtract(expected); // dCost/dOut ~= (y - yhat);
    for (int i = depth - 1; i >= 0; i--) {
        Layer* layer = layers[i];

        if (layer->type == LayerType::Dense) {
            Dense* dense = ((Dense *) layer);

            Matrix* dcdw = Ops::matmul(neurons[i]->transpose(), dcdb);
            Matrix* dcdb_t = dcdb->copy();

            dense->weights = dense->weights->subtract(dcdw->scale(rate));
            dense->biases = dense->biases->subtract(dcdb_t->scale(rate));

            delete dcdw;
            delete dcdb_t;

            Matrix* new_dcdb = Ops::matmul(dcdb, dense->weights->copy()->transpose());
            delete dcdb;
            dcdb = new_dcdb;
        }
        else if (layer->type == LayerType::ActivationFn) {
            Matrix* activated = ((ActivationLayer *) layer)->dactivate(neurons[i]->copy());

            dcdb->shur_fast(activated);

            delete activated;
        }
    }
    delete dcdb;
}



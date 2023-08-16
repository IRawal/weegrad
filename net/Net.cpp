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
void Net::train(Matrix *in, Matrix *expected, double rate) {
    for (int eps = 0; eps < 100; eps++) {
        Matrix* newIn = in->clone();
        Matrix* out = forward(newIn);
        //printf("Out: %f\n", out->elements[0][0]);
        Matrix* dcda = Ops::subtract(&neurons[depth], expected); // dCost/dOut ~= (y - yhat);

        //double dcdb = dcda->elements[0][0];
        Matrix* dcdb = dcda;

        for (int i = depth - 1; i >= 0; i--) {
            Layer* layer = layers[i];

            if (layer->type == LayerType::Dense) {
                Dense* dense = ((Dense *) layer);

                Matrix* dcdw = Ops::matmul(dcdb->transpose(), &neurons[i]);

                ((Dense *) layer)->weights = Ops::subtract(dense->weights, dcdw->broadcast([&rate](double d) -> double {return d * rate;})->transpose());
                ((Dense *) layer)->biases = Ops::subtract(dense->biases, dcdb->clone()->transpose()->broadcast([&rate](double d) -> double {return d * rate;}));

                //dcdb *= ((Dense*) layers[i])->weights->elements[0][0];
                if (i != 0)
                    dcdb = Ops::matmul(dcdb, dense->weights->clone()->transpose());
                //double dcdw = dcdb * neurons[i].elements[0][0];


                //((Dense *) layer)->weights->elements[0][0] -= dcdw * rate;
                //((Dense *) layer)->biases->elements[0][0] -= dcdb * rate;


            }
            else if (layer->type == LayerType::ActivationFn) {
                dcdb = Ops::schur(dcdb, neurons[i].broadcast(&ReLU::drelu));
                //dcdb *= neurons[i].broadcast(&ReLU::drelu);
            }
        }
    }
}


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

std::vector<Layer*> layers;
Matrix* neurons;
int depth;

Net::Net(std::vector<Layer*> layers, int depth) {
    this->layers = layers;
    this->depth = depth;
    neurons = static_cast<Matrix*>(malloc(sizeof(Matrix) * (depth + 1)));
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
void Net::train(Matrix *in, Matrix *expected) {
    for (int i = 0; i < 1000; i++) {
        Matrix* newIn = in->clone();
        Matrix* out = forward(newIn);
        printf("Out: %f\n", out->elements[0][0]);

        double mse = loss(out, expected);
        printf("Loss: %f\n", mse);

        Matrix* dcda = Ops::subtract(&neurons[depth], expected)->broadcast(
                [](double d) -> double { return d * 2; }); // dCost/dOut = 2(y - yhat)


        double dzdw = in->elements[0][0] * dcda->elements[0][0];

        printf("dzdw: %f\n", dzdw);

        ((Dense*)layers[0])->weights->elements[0][0] -= 0.01 * dzdw;
        ((Dense*)layers[0])->biases->elements[0][0] -= 0.01 * dcda->elements[0][0];

        printf("Weight: %f\n", (((Dense *) layers[0])->weights->elements[0][0]));
        printf("Bias: %f\n", (((Dense *) layers[0])->biases->elements[0][0]));
    }
}


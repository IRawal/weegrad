//
// Created by isha on 8/7/23.
//

#include "nn.h"
#include "linearalg/matrix.h"

#include <cstdlib>

matrix* layers;

nn::nn(int inRows, int inCols, int hiddenSize, int hiddenLayers, int outRows, int outCols) {
    int totalLayers = hiddenLayers + 2;
    // Expand input matrix to be square with size of hidden
    layers = static_cast<matrix*>(malloc(sizeof(matrix*) * totalLayers));
    layers[0] = matrix(inCols, totalLayers);

    for (int i = 1; i < hiddenLayers + 1; i++) {
        layers[i] = matrix(hiddenSize, hiddenSize);
    }

    layers[totalLayers - 1] = matrix(hiddenSize, 1);
}
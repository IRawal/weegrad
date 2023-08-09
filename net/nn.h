//
// Created by isha on 8/7/23.
//

#ifndef WEEGRAD_NN_H
#define WEEGRAD_NN_H


#include "../linearalg/matrix.h"
#include "dense.h"

class nn {
    public:
        nn(dense *layers, int depth);
        matrix forward(matrix *in, double (*fn)(double));
        matrix train(matrix *in, matrix *expected);
        static double relu(double x);
    dense* layers;
    matrix* neurons;
    int depth;
};


#endif //WEEGRAD_NN_H

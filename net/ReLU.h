//
// Created by isha on 8/10/23.
//

#ifndef WEEGRAD_RELU_H
#define WEEGRAD_RELU_H


#include "Layer.h"

class ReLU : public Layer {
    public:
        Matrix forward(Matrix *in);
        static double drelu(double x);
        static double relu(double x);
};


#endif //WEEGRAD_RELU_H

//
// Created by isha on 8/7/23.
//

#ifndef WEEGRAD_NET_H
#define WEEGRAD_NET_H


#include <vector>
#include "../linearalg/Matrix.h"
#include "layers/Dense.h"

class Net {
    public:
        Net(Layer **layers, int depth);
        Matrix * forward(Matrix *in);
        void train(Matrix **xs, Matrix **ys, int examples, float rate, int epochs);
        void step(Matrix *expected, float rate);
        Layer** layers;
        Matrix** neurons;
        int depth;
};


#endif //WEEGRAD_NET_H

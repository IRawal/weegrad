//
// Created by isha on 8/8/23.
//

#ifndef WEEGRAD_DENSE_H
#define WEEGRAD_DENSE_H


#include "../../linearalg/Matrix.h"
#include "../Layer.h"

class Dense : public Layer {
    public:
        Dense(int inLen, int outLen);
        Matrix * forward(Matrix *in) override;
        Matrix* weights;
        Matrix* biases;
};


#endif //WEEGRAD_DENSE_H

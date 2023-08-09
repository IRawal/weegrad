//
// Created by isha on 8/8/23.
//

#ifndef WEEGRAD_DENSE_H
#define WEEGRAD_DENSE_H


#include "../linearalg/matrix.h"

class dense {
    public:
        dense(int inLen, int outLen);
        matrix forward(matrix *in);
        matrix* weights;
        matrix* biases;
};


#endif //WEEGRAD_DENSE_H

//
// Created by isha on 8/7/23.
//

#ifndef WEEGRAD_NN_H
#define WEEGRAD_NN_H


#include "linearalg/matrix.h"

class nn {
    public:
        nn(matrix *layers, int netDepth);
        matrix forward(matrix in);
};


#endif //WEEGRAD_NN_H

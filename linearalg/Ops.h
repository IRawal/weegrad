//
// Created by isha on 8/6/23.
//

#ifndef WEEGRAD_OPS_H
#define WEEGRAD_OPS_H


#include "Matrix.h"

class Ops {
    public:
        int rows;
        int cols;
        static Matrix * matmul(Matrix *m1, Matrix *m2);
        static Matrix *rowSum(Matrix *in);
        static Matrix *colSum(Matrix *in);
};


#endif //WEEGRAD_OPS_H

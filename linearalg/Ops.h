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
        static Matrix * matmul_fast(Matrix *m1, Matrix *m2);
        static Matrix *rowSum(Matrix *in);
        static Matrix *colSum(Matrix *in);
        static void shuffle(Matrix **m1, Matrix **m2, int n);
};


#endif //WEEGRAD_OPS_H

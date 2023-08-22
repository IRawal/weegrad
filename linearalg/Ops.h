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
        static void vec_shur_fast(float* v1, float* v2, int len);
};


#endif //WEEGRAD_OPS_H

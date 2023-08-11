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
        static Matrix multiply(Matrix *m1, Matrix *m2);
        static Matrix add(Matrix *m1, Matrix *m2);
        static Matrix subtract(Matrix *m1, Matrix *m2);
};


#endif //WEEGRAD_OPS_H

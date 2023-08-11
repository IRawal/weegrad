//
// Created by isha on 8/6/23.
//

#ifndef WEEGRAD_OPS_H
#define WEEGRAD_OPS_H


#include "matrix.h"

class ops {
    public:
        int rows;
        int cols;
        static matrix multiply(matrix *m1, matrix *m2);
        static matrix add(matrix *m1, matrix *m2);
        static matrix subtract(matrix *m1, matrix *m2);
};


#endif //WEEGRAD_OPS_H

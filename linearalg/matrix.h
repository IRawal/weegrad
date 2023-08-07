//
// Created by isha on 8/6/23.
//

#ifndef WEEGRAD_MATRIX_H
#define WEEGRAD_MATRIX_H


class matrix {
    public:
        matrix(int rows, int cols);

    matrix transpose();

    matrix resize();

    void free();
};


#endif //WEEGRAD_MATRIX_H

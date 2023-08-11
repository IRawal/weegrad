//
// Created by isha on 8/6/23.
//

#ifndef WEEGRAD_MATRIX_H
#define WEEGRAD_MATRIX_H


class matrix {
    public:
        int rows;
        int cols;
        double** elements;

        matrix(int rows, int cols);

        matrix transpose();

        matrix resize(int r, int c);

        void m_free();

        void print();

        matrix randomize();

        double** m_allocate(int r, int c);

        matrix broadcast(double (*fn)(double));

    matrix clone();
};


#endif //WEEGRAD_MATRIX_H

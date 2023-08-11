//
// Created by isha on 8/6/23.
//

#ifndef WEEGRAD_MATRIX_H
#define WEEGRAD_MATRIX_H


class Matrix {
    public:
        int rows;
        int cols;
        double** elements;

        Matrix(int rows, int cols);

        Matrix transpose();

        Matrix resize(int r, int c);

        void m_free();

        void print();

        Matrix * randomize();

        double** m_allocate(int r, int c);

        Matrix * broadcast(double (*fn)(double));

        Matrix * clone();

        double sum();
};


#endif //WEEGRAD_MATRIX_H

//
// Created by isha on 8/6/23.
//

#include <functional>

#ifndef WEEGRAD_MATRIX_H
#define WEEGRAD_MATRIX_H


class Matrix {
    public:
        int rows;
        int cols;
        double** elements;

        Matrix(int rows, int cols);

        Matrix * transpose();

        Matrix * resize(int r, int c);

        void m_free();

        void print();

        Matrix * randomize();

        double** m_allocate(int r, int c);

        Matrix * broadcast(std::function<double(double)> fn);

        Matrix * copy();

        double sum();

        ~Matrix();
};


#endif //WEEGRAD_MATRIX_H

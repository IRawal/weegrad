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
        float** elements;

        Matrix(int rows, int cols);

        Matrix * transpose();

        Matrix * resize(int r, int c);

        void m_free();

        void print();

        Matrix * randomize();

        float** m_allocate(int r, int c);

        Matrix * broadcast(std::function<float(float)> fn);

        Matrix * copy();

        Matrix *scale(float d);

        Matrix *subtract(Matrix *m2);

        Matrix *add(Matrix *m2);

        Matrix *add_fast(Matrix *m2);

        Matrix *shur(Matrix *m2);

        float sum();

        Matrix *fill(float d);

        ~Matrix();


    Matrix *shur_fast(Matrix *m2);
};



#endif //WEEGRAD_MATRIX_H

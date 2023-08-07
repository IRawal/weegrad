//
// Created by isha on 8/6/23.
//

#ifndef WEEGRAD_MATRIX_H
#define WEEGRAD_MATRIX_H


class matrix {
    public:
        matrix(int rows, int cols);

        void transpose();

        void resize(int r, int c);

        void m_free();

        void print();

        void randomize();

        double** m_allocate(int r, int c);
};


#endif //WEEGRAD_MATRIX_H

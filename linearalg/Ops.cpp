//
// Created by isha on 8/6/23.
//

#include <cstdlib>
#include <cstdio>
#include <numeric>
#include <iostream>
#include <random>
#include <emmintrin.h>

#include "Ops.h"
#include "Matrix.h"

Matrix* Ops::matmul_fast(Matrix *m1, Matrix *m2) {
    if (m1->cols != m2->rows) {
        printf("Invalid dimensions\n");
        exit(-1);
    }

    Matrix* product = new Matrix(m1->rows, m2->cols);
    const int m1Rows = m1->rows;
    const int m1Cols = m1->cols;
    const int m2Cols = m2->cols;

    for (int i = 0; i < m1Rows; ++i) {
        for (int j = 0; j < m2Cols; ++j) {
            __m128d accum = _mm_setzero_pd(); // Initialize a vector accumulator

            for (int k = 0; k < m1Cols; k += 2) {
                __m128d m1Vec = _mm_loadu_pd(&m1->elements[i][k]); // Load 2 doubles from m1
                __m128d m2Vec = _mm_loadu_pd(&m2->elements[k][j]); // Load 2 doubles from m2
                accum = _mm_add_pd(accum, _mm_mul_pd(m1Vec, m2Vec)); // Multiply and accumulate
            }

            double n[2];
            _mm_storeu_pd(n, accum); // Store the accumulated result back to an array
            product->elements[i][j] = n[0] + n[1]; // Sum the elements in the array
        }
    }
    return product;
}
Matrix* Ops::matmul(Matrix *m1, Matrix *m2) {
    //checking the dimensions of the input matrices
    if (m1->cols != m2->rows) {
        printf("invalid dimensions\n");
        exit(-1);
    }
    Matrix* product = new Matrix(m1->rows, m2->cols);

    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m2->cols; j++) {
            double n = 0;
            for (int k = 0; k < m1->cols; k++) {
                n += m1->elements[i][k] * m2->elements[k][j];
            }
            product->elements[i][j] = n;
        }
    }
    return product;
}
Matrix* Ops::rowSum(Matrix *in) {
    Matrix* newMat = new Matrix(in->rows, 1);
    for (int i = 0; i < in->rows; i++) {
        double sum = 0;
        for (int j = 0; j < in->cols; j++) {
            sum += in->elements[i][j];
        }
        newMat->elements[i][0] = sum;
    }
    return newMat;
}
Matrix* Ops::colSum(Matrix *in) {
    Matrix* newMat = new Matrix(1, in->cols);
    for (int i = 0; i < in->cols; i++) {
        double sum = 0;
        for (int j = 0; j < in->rows; j++) {
            sum += in->elements[j][i];
        }
        newMat->elements[0][i] = sum;
    }
    return newMat;
}
/*Shuffles column vectors of length n while retaining same indices for both vectors*/
void Ops::shuffle(Matrix **m1, Matrix **m2, int n) {
    std::vector<int> indices = std::vector<int>(n);
    std::iota(std::begin(indices), std::end(indices), 0);
    std::shuffle(std::begin(indices), std::end(indices), std::random_device());
    for (int i = 0; i < n; i++) {
        Matrix* tmp = m1[indices[i]];
        m1[indices[i]] = m1[i];
        m1[i] = tmp;

        tmp = m2[indices[i]];
        m2[indices[i]] = m2[i];
        m2[i] = tmp;
    }
}


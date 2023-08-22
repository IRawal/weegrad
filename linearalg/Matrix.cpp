//
// Created by isha on 8/6/23.
//
#include "Matrix.h"

#include "../net/ActivationLayer.h"

#include <cstdlib>
#include <iostream>
#include <functional>
#include <emmintrin.h>
#include <immintrin.h>

double** elements;
int rows;
int cols;

Matrix::Matrix(int r, int c) {
    rows = r;
    cols = c;
    elements = m_allocate(r, c);
}
Matrix* Matrix::resize(int r, int c) {
    if (rows * cols != r * c)
        exit(-1);
    double** newEls = m_allocate(r, c);
    // Go through each element and place into new Matrix
    int rCtr = -1;
    int newRCtr = -1;
    for (int i = 0; i < rows * cols; i++) {
        if (i % c == 0)
            newRCtr++;
        if (i % cols == 0)
            rCtr++;
        newEls[newRCtr][i % c] = elements[rCtr][i % cols];
    }
    m_free();

    rows = r;
    cols = c;
    elements = newEls;
    return this;
}
Matrix* Matrix::transpose() {
    resize(cols, rows);
    return this;
}
double** Matrix::m_allocate(int r, int c) {
    double** els = static_cast<double **>(malloc(r * sizeof(double *)));
    for (int i = 0; i < r; i++) {
        els[i] = static_cast<double *>(malloc(c * sizeof(double *)));
    }
    return els;
}
void Matrix::m_free() {
    for (int i = 0; i < rows; i++) {
        free(elements[i]);
    }
    free(elements);
}
void Matrix::print() {
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            printf("%f ", elements[i][k]);
        }
        printf("%s", "\n");
    }
}
Matrix* Matrix::randomize() {
    srand(time(nullptr));
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            elements[i][k] = (double) rand() / RAND_MAX;
        }
    }
    return this;
}
Matrix* Matrix::broadcast(std::function<double(double)> fn) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            elements[i][j] = fn(elements[i][j]);
        }
    }
    return this;
}
Matrix* Matrix::scale(double d) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            elements[i][j] = elements[i][j] * d;
        }
    }
    return this;
}
Matrix* Matrix::fill(double d) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            elements[i][j] = d;
        }
    }
    return this;
}
Matrix* Matrix::subtract(Matrix *m2) {
    if (rows != m2->rows || cols != m2->cols) {
        printf("invalid dimensions\n");
        exit(-1);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            elements[i][j] = elements[i][j] - m2->elements[i][j];
        }
    }
    return this;
}
Matrix* Matrix::add(Matrix *m2) {
    if (rows != m2->rows || cols != m2->cols) {
        printf("invalid dimensions\n");
        exit(-1);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            elements[i][j] = elements[i][j] + m2->elements[i][j];
        }
    }
    return this;
}
/* AVX accelerated addition */
Matrix* Matrix::add_fast(Matrix *m2) {
    if (rows != m2->rows || rows != 1 || cols != m2->cols) {
        printf("invalid dimensions\n");
        exit(-1);
    }
    for (int i = 0; i < cols; i += 2) {
        __m256d v1 = _mm256_load_pd(elements[0] + i);
        __m256d v2 = _mm256_load_pd(m2->elements[0] + i);
        __m256d out = _mm256_add_pd(v1, v2);
        _mm256_stream_pd(elements[0] + i, out);
    }
    return this;
}
Matrix* Matrix::shur(Matrix *m2) {
    if (rows != m2->rows || cols != m2->cols) {
        printf("invalid dimensions\n");
        exit(-1);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            elements[i][j] = elements[i][j] * m2->elements[i][j];
        }
    }
    return this;
}
Matrix* Matrix::copy() {
    Matrix* newMat = new Matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newMat->elements[i][j] = elements[i][j];
        }
    }
    return newMat;
}
double Matrix::sum() {
    double sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += elements[i][j];
        }
    }
    return sum;
}
Matrix::~Matrix() {
    m_free();
}



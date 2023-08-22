//
// Created by isha on 8/6/23.
//
#include "Matrix.h"

#include "../net/ActivationLayer.h"
#include "Ops.h"

#include <cstdlib>
#include <iostream>
#include <functional>
#include <emmintrin.h>
#include <immintrin.h>

float** elements;
int rows;
int cols;

Matrix::Matrix(int r, int c) {
    rows = r;
    cols = c;
    elements = m_allocate(r, c);
}
float** Matrix::m_allocate(int r, int c) {
    float** els = static_cast<float **>(malloc(r * sizeof(float *)));
    for (int i = 0; i < r; i++) {
        //els[i] = static_cast<float *>(malloc(c * sizeof(float)));
        els[i] = static_cast<float *>(aligned_alloc(64, c * (sizeof(float))));
    }
    return els;
}

Matrix* Matrix::resize(int r, int c) {
    if (rows * cols != r * c)
        exit(-1);
    float** newEls = m_allocate(r, c);
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
            elements[i][k] = (float) rand() / RAND_MAX;
        }
    }
    return this;
}
Matrix* Matrix::broadcast(std::function<float(float)> fn) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            elements[i][j] = fn(elements[i][j]);
        }
    }
    return this;
}
Matrix* Matrix::scale(float d) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            elements[i][j] = elements[i][j] * d;
        }
    }
    return this;
}
Matrix* Matrix::fill(float d) {
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
    for (int i = 0; i < rows; i++) {
        int leftover = cols % 8;
        float *v = elements[i];
        for (int j = 0; j < cols - leftover; j += 8) {
            __m256 v1 = _mm256_load_ps(v + j);
            __m256 v2 = _mm256_load_ps(m2->elements[i] + j);
            __m256 out = _mm256_add_ps(v1, v2);
            _mm256_stream_ps(v + j, out);
        }
        for (int j = cols - leftover; j < cols; j++) {
            v[j] += m2->elements[i][j];
        }
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
Matrix* Matrix::shur_fast(Matrix *m2) {
    if (rows != m2->rows || rows != 1 || cols != m2->cols) {
        printf("invalid dimensions\n");
        exit(-1);
    }
    for (int i = 0; i < rows; i++) {
        float *v = elements[i];
        Ops::vec_shur_fast(v, m2->elements[i], cols);
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
float Matrix::sum() {
    float sum = 0;
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



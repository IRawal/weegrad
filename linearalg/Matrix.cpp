//
// Created by isha on 8/6/23.
//

#include <cstdlib>
#include <iostream>

#include "Matrix.h"

double** elements;
int rows;
int cols;

Matrix::Matrix(int r, int c) {
    rows = r;
    cols = c;
    elements = m_allocate(r, c);
}
Matrix Matrix::resize(int r, int c) {
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
    return *this;
}
Matrix Matrix::transpose() {
    resize(cols, rows);
    return *this;
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
    srand(time(0));
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            elements[i][k] = (double) rand() / RAND_MAX;
        }
    }
    return this;
}
Matrix* Matrix::broadcast(double (*fn)(double)) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            elements[i][j] = fn(elements[i][j]);
        }
    }
    return this;
}
Matrix* Matrix::clone() {
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
}
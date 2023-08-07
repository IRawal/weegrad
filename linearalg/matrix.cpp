//
// Created by isha on 8/6/23.
//

#include <cstdlib>
#include <iostream>

#include "matrix.h"

double** elements;
int rows;
int cols;

matrix::matrix(int r, int c) {
    rows = r;
    cols = c;
    elements = m_allocate(r, c);
}
void matrix::resize(int r, int c) {
    if (rows * cols != r * c)
        exit(-1);
    double** newEls = m_allocate(r, c);
    // Go through each element and place into new matrix
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
}
void matrix::transpose() {
    resize(cols, rows);
}
double** matrix::m_allocate(int r, int c) {
    double** els = static_cast<double **>(malloc(r * sizeof(double *)));
    for (int i = 0; i < r; i++) {
        els[i] = static_cast<double *>(malloc(c * sizeof(double *)));
    }
    return els;
}
void matrix::m_free() {
    for (int i = 0; i < rows; i++) {
        free(elements[i]);
    }
    free(elements);
}
void matrix::print() {
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            printf("%f ", elements[i][k]);
        }
        printf("%s", "\n");
    }
}
void matrix::randomize() {
    srand(time(0));
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            elements[i][k] = (double) rand() / RAND_MAX;
        }
    }
}
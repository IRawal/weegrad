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
    elements = static_cast<double **>(malloc(rows * sizeof(double *)));
    for (int i = 0; i < rows; i++) {
        elements[i] = static_cast<double *>(malloc(cols * sizeof(double *)));
    }
}

matrix matrix::transpose() {

}
matrix matrix::resize() {

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
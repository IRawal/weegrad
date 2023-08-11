//
// Created by isha on 8/6/23.
//

#include <cstdlib>
#include <cstdio>
#include "ops.h"
#include "matrix.h"

matrix ops::multiply(matrix *m1, matrix *m2) {
    //checking the dimensions of the input matrices
    if (m1->cols != m2->rows) {
        printf("invalid dimensions\n");
        exit(-1);
    }
    matrix product = matrix(m1->rows, m2->cols);

    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m2->cols; j++) {
            double n = 0;
            for (int k = 0; k < m1->cols; k++) {
                n += m1->elements[i][k] * m2->elements[k][j];
            }
            product.elements[i][j] = n;
        }
    }
    return product;
}
matrix ops::add(matrix *m1, matrix *m2) {
    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        printf("invalid dimensions\n");
        exit(-1);
    }
    matrix out = matrix(m1->rows, m1->cols);
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            out.elements[i][j] = m1->elements[i][j] + m2->elements[i][j];
        }
    }
    return out;
}
matrix ops::subtract(matrix *m1, matrix *m2) {
    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        printf("invalid dimensions\n");
        exit(-1);
    }
    matrix out = matrix(m1->rows, m1->cols);
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            out.elements[i][j] = m1->elements[i][j] - m2->elements[i][j];
        }
    }
    return out;
}

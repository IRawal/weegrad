//
// Created by isha on 8/6/23.
//

#include <cstdlib>
#include <cstdio>
#include "ops.h"
#include "matrix.h"

matrix ops::multiply(matrix m1, matrix m2) {
    //checking the dimensions of the input matrices
    if (m1.cols != m2.rows) {
        printf("invalid dimensions\n");
        exit(-1);
    }

    //allocating the memory for the new matrix
    matrix product = matrix(m1.cols, m2.rows);

    //doing the actual multiplication
    int m1rowc, m2colc, counter, cellsum = 0;
    for (m1rowc = 0; m1rowc < product.rows; ++m1rowc) {
        for (m2colc = 0; m2colc < product.cols; ++m2colc) {
            for (counter = 0; counter < m1.rows; ++counter) {
                cellsum += m1.elements[m1rowc][counter] * m2.elements[counter][m2colc];
            }
            product.elements[m1rowc][m2colc] = cellsum;
        }
    }
    return product;
}

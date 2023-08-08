#include <iostream>

#include "linearalg/matrix.h"
#include "linearalg/ops.h"

int main() {
    matrix m1 = matrix(2, 2);

    m1.elements[0][0] = 1;
    m1.elements[0][1] = 1;
    m1.elements[1][1] = 1;


    matrix m2 = matrix(2, 2);

    m2.elements[0][0] = 1;
    m2.elements[1][0] = 1;

    ops::multiply(m1, m2).print();
    return 0;
}

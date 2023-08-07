#include <iostream>

#include "linearalg/matrix.h"
#include "linearalg/ops.h"

int main() {
    matrix m1 = matrix(1, 2);
    matrix m2 = matrix(2, 1);
    ops::multiply(m1, m2).print();
    return 0;
}
